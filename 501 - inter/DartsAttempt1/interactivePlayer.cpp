#include "interactivePlayer.h"
#include <iostream>
#include <Windows.h>
using namespace std;



interactivePlayer::interactivePlayer() {
	
}

void interactivePlayer::DeductPoints(int score) {
	setScore(getScore() - score);
}

void interactivePlayer::aimAndThrow(bool* RoundWon) {
	int target = 0;
	int multiplierTarget = 0;

	setScoreBuffer(getScore());

	for (int i = 0; i < 3; i++) {

		target = 0;

		cout  << endl<< "What multiplier would you like to aim for? " << endl;
		cout << "1 = single " << endl;
		cout << "2 = double " << endl;
		cout << "3 = treble " << endl;
		cout << "4 = bullseye " << endl;
		cout << "5 = outer bullseye " << endl;

		cin >> multiplierTarget;
		switch (multiplierTarget) {

		case 1:
			while (target <=0 || target > 20) {
				cout << "Enter value 0  - 20 on which you would like to aim for" << endl;
				cin >> target;
			}
			// throw single
			DeductPoints(throw_single(target, getSuccessRate()));

			if (getScore() < 0) {
				setScore(GetScoreBuffer());
				cout << "Game did Not end on double or bull, resetting score to " << getScore() << endl;
			} 
		//	cout << "player 1 score " << getScore() << endl;

			break;
		case 2:
			while (target <= 0 || target > 20) {
				cout << "Enter value 0  - 20 on which you would like to aim for" << endl;
				cin >> target;
			}
			DeductPoints(throw_double(target, getSuccessRate()));

			if (getScore() == 0) {
				*RoundWon = true;
				increaseRoundWins();
			
				cout << "round won by player 1!" << endl;
			}
			else if (getScore() < 0) {
				
				setScore(GetScoreBuffer());
			cout << "bust! score reset to " << getScore();
			}

			break;
		case 3:
			while (target <= 0 || target > 20) {
				cout << "Enter value 0  - 20 on which you would like to aim for" << endl;
				cin >> target;
			}

			DeductPoints(throw_treble(target, getSuccessRate()));
			if (getScore() == 0 || getScore() < 0) {
				setScore(GetScoreBuffer());
				cout << "Game did Not end on double or bull, resetting score to " << getScore();
			}
	
		//	cout << "player 1 score " << getScore() << endl;
	
			break;

		case 4:
			cout << "Aiming for bull" << endl;
			DeductPoints(throw_bull(getSuccessRate()));

			if (getScore() == 0) {
				*RoundWon = true;
				increaseRoundWins();
			}
			else if (getScore() < 0) {
				setScore(GetScoreBuffer());
			}
		
			//cout << "player 1 score " << getScore() << endl;
		
			break;
		case 5:
			cout << "Aiming for outerbull" << endl;
			DeductPoints(throw_single(25, getSuccessRate()));

			if (getScore() == 0 || getScore() < 0) {
				setScore(GetScoreBuffer());
				cout << "Game did Not end on double or bull, resetting score to " << getScore() << endl;
			}
	
			//cout << "player 1 score " << getScore() << endl;
		

			break;
		}
					
	
	



		if (*RoundWon == true) {
			// break out of loop condition
			i = 3;
		}
	}

	cout << "____________" << endl;
	cout << "|    Joe:   |" << endl;
	cout << "|           |" << endl;
	cout << "|     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		cout << getScore();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "   |" << endl;
	cout << "|           |" << endl;
	cout << "|    Sid:   |" << endl;
	cout << "|     ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << getScore();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "   |" << endl;
	cout << " __________" << endl;


}

