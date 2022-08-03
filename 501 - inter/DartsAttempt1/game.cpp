#include "game.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
//#include <>
using namespace std;

game::game() {
	ScoreCount[0][0] = 0; ScoreCount[0][1] = 0; ScoreCount[0][2] = 0; ScoreCount[0][3] = 0; ScoreCount[0][4] = 0; ScoreCount[0][5] = 0; ScoreCount[0][6] = 0;
	ScoreCount[1][0] = 0; ScoreCount[1][1] = 0; ScoreCount[1][2] = 0; ScoreCount[1][3] = 0; ScoreCount[1][4] = 0; ScoreCount[1][5] = 0; ScoreCount[1][6] = 0;
}

game::~game() {

}
void game::updateList(player* player) {
	int throws = player->getTurns();
	gameLengths.push_back(throws);

}


double game::findmax() {

	double max = 0;

	for (int i = 0; i < gameLengths.size(); i++) {
		if (gameLengths[i] > max) {
			max = gameLengths[i];
		}
	}
	return max;
}
double game::countOccurances(int target) {
	double occurances = 0;

	for (int i = 0; i < gameLengths.size(); i++) {
		if (gameLengths[i] == target) {
			occurances++;
		}
	}

	return occurances;
}

void game::countScores(player* player, int gamesPlayed) {
	int row = 0;

if (player->getName() == "joe") {
	row = 0;
}
else {
	row = 1;
}


	// outerloop which controls which number is being counted
	for (int i = 0; i < 7; i++)
	{
			// inner loop which traverses array
			for (int j = 0; j < player->getLength(); j++) {
				// count occurances for 0-6
				if (player->returnElement(j) == i)
				{
					// array which is from 0 - 6
					ScoreCount[row][i] = ScoreCount[row][i] + 1;
				}
			}	
	}
}


void game::outputScores(int NoGames, player* player1, player* player2) {
	

	cout << endl;

	cout << "joe : sid" << endl;
	cout << "0:7" << " " << ScoreCount[0][0] / NoGames * 100 << "%"<< endl;
	cout << "1:7" << " " << ScoreCount[0][1] / NoGames * 100 << "%" << endl;
	cout << "2:7" << " " << ScoreCount[0][2] / NoGames * 100 << "%" << endl;
	cout << "3:7" << " " << ScoreCount[0][3] / NoGames * 100 << "%" << endl;
	cout << "4:7" << " " << ScoreCount[0][4] / NoGames * 100 << "%" << endl;
	cout << "5:7" << " " << ScoreCount[0][5] / NoGames * 100 << "%" << endl;
	cout << "6:7" << " " << ScoreCount[0][6] / NoGames * 100 << "%" << endl;

	cout << "7:0" << " " << ScoreCount[1][0] / NoGames * 100 << "%" << endl;
	cout << "7:1" << " " << ScoreCount[1][1] / NoGames * 100 << "%" << endl;
	cout << "7:2" << " " << ScoreCount[1][2] / NoGames * 100 << "%" << endl;
	cout << "7:3" << " " << ScoreCount[1][3] / NoGames * 100 << "%" << endl;
	cout << "7:4" << " " << ScoreCount[1][4] / NoGames * 100 << "%" << endl;
	cout << "7:5" << " " << ScoreCount[1][5] / NoGames * 100 << "%" << endl;
	cout << "7:6" << " " << ScoreCount[1][6] / NoGames * 100 << "%" << endl;
	
	cout << endl;


}


int game::decideFirst(player* player1, player* player2) {


	
	// declaration of variables used to work out who was closer to bull
	int p1TempScore = 0;
	int p2TempScore = 0;
	int p1Dif = 0;
	int p2Dif = 0;

	// loop that will run until one player doesn't hit a bull, it will also run if they both hit 20 for example
	do {
		p1TempScore =  p1TempScore + player1->throw_bull(player1->getSuccessRate());


		p2TempScore = p2TempScore  + player2->throw_bull(player2->getSuccessRate());

	} while (p1TempScore == p2TempScore);

	

	// calling workDif function which works out the difference between the score hit and 50
	if (workDif(p1TempScore) < workDif(p2TempScore)) {
		// return value indicating which player is to start (i.e 1 or 2)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // sets colour of text
		cout << endl << "player 2 will throw first" << endl;	
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		return 1;
		
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		cout << endl << "player 1 will throw first" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		return 2;
	}
	

	
}

int game::workDif(int score) {
	// function which works out the difference which will help workout who is closer to hitting the bull
	int dif;
	if (score > 50) {
		dif = score - 50;
	}
	else {
		dif = 50 - score;
	}
	return dif;
}




void game::PlayGame(player* player1, player* player2, int noGames) {


	//  variables used to control the loops
	bool RoundWon = false;
	bool* RoundWonPTR = &RoundWon; // pointer to the above variable

	bool setWon = false;
	bool gameWon = false;


	// decide who throws first
	int throwFirst = 0;
	throwFirst = decideFirst(player1, player2);

	for (int i = 0; i < noGames; i++) {

		if (i < noGames) { // keep setting gameWon to false if the loop is not finished
			gameWon = false; 
		}


		// <----------------------- GAME ------------------------>
		
		// setting sets to 0 before entering first nested loop
		player1->setSetsWon(0);
		player2->setSetsWon(0);

		while (!gameWon) // nested loop to control if the game has been won yet (first to 13)
		{

			setWon = false;
			// setting the rounds won to 0 before entering second nested loop
			player1->setRoundsWon(0);
			player2->setRoundsWon(0);
			// <----------------------- SET ------------------------>
			while (!setWon) { // loop to control if the set has been won ( best of 5)

				// setting round won to false 
				player1->setWonRound(false);
				player2->setWonRound(false);
				// setting score to 501
				player1->setScore(501);
				player2->setScore(501);

				// flip flops the player starting first ( This is why the throw first function returns the opposite, because it will flip anyway to what it should be)
				switch (throwFirst) {
				case 1: throwFirst = 2; break;
				case 2: throwFirst = 1; break;
				default: cout << "Error"; // catch all error statement 
				}

				// <----------------------- round ------------------------>
				while (!RoundWon) // loop to control if the round has been won (501 - 0)
				{
					if (throwFirst == 1) // if the throw first variable is 1 then player 1 should throw first(this will be switched next round)
					{
						
						player1->take_turn(RoundWonPTR);	// player 1 turn (throw 3 darts)
						
						if (!RoundWon) { // if the game is not won player 2 (chaser) throws 
							player2->take_turn(RoundWonPTR);	// player 2 turn
						}
					}
					else if (throwFirst == 2) {
						
						player2->take_turn(RoundWonPTR);	// player 1 turn
						
						if (!RoundWon) { // if the game is not won player 2 (chaser) throws 
							player1->take_turn(RoundWonPTR);	// player 2 turn
						}



					}
				}
				// restart round
				RoundWon = false;

				// checking if a player has won a set and which player has won it and incrementing the value accordingly 
				if (player1->getRoundsWon() == 3) {
					player1->increaseSetWins();
					
				//	cout << "player 1 has won this set and has now won " << player1->getSetsWon() << endl;

					player1->setRoundsWon(0);
					player2->setRoundsWon(0);
					setWon = true;

				}
				else if (player2->getRoundsWon() == 3) {
					player2->increaseSetWins();

					//cout << "player 2 has won this set and has won " << player2->getSetsWon() << endl;

					player1->setRoundsWon(0);
					player2->setRoundsWon(0);
					setWon = true;
				}



			}
			// checking if a player has won a game and which player has won it and incrementing the value accordingly 
			if (player1->getSetsWon() == 7 || player2->getSetsWon() == 7) {
				gameWon = true;
				// pushing scores onto array
				player1->push_score(player1->getSetsWon());
				player2->push_score(player2->getSetsWon());
			}
		}
	}
}









void game::playInteractiveGame(interactivePlayer* player1, player* player2) {

	bool RoundWon = false;
	bool* RoundWonPTR = &RoundWon;

	bool setWon = false;
	bool gameWon = false;




	// decide throw first
	int throwFirst = 0;
	throwFirst = decideFirst(player1, player2);

	
		// <----------------------- GAME ------------------------>

		player1->setSetsWon(0);
		player2->setSetsWon(0);
		while (!gameWon)
		{

			setWon = false;

			player1->setRoundsWon(0);
			player2->setRoundsWon(0);
			// <----------------------- SET ------------------------>
			while (!setWon) {

				player1->setWonRound(false);
				player2->setWonRound(false);

				player1->setScore(501);
				player2->setScore(501);

				// flip flops the player starting first ( This is why the throw first function returns the opposite, because it will flip anyway to what it should be)
				switch (throwFirst) {
				case 1: throwFirst = 2; break;
				case 2: throwFirst = 1; break;
				default: cout << "Error";
				}

				// <----------------------- round ------------------------>
				while (!RoundWon)
				{
					if (throwFirst == 1)
					{
						
						//cout << endl;
						player1->aimAndThrow(RoundWonPTR);	// player 1 turn
						if (!RoundWon) { // if the game is not won player 2 (chaser) throws 
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
							player2->take_turn(RoundWonPTR);	// player 2 turn
							
							cout << "player 2 score " << player2->getScore() << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						}
					}
					else if (throwFirst == 2) {
						//	cout << endl;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						player2->take_turn(RoundWonPTR);	// player 1 turn
						
						cout << "player 2 score " << player2->getScore() << endl ;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						//cout << endl;
						if (!RoundWon) { // if the game is not won player 2 (chaser) throws 
							player1->aimAndThrow(RoundWonPTR);	// player 2 turn
				
						}



					}
				}
				// restart round
				cout << "Round over!" << ": next round starting..." << endl;
				RoundWon = false;

				if (player1->getRoundsWon() == 3) {
					player1->increaseSetWins();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
					cout << endl << "Player 1 has won this set, now has won " << player1->getSetsWon();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					player1->setRoundsWon(0);
					player2->setRoundsWon(0);
					setWon = true;

				}
				else if (player2->getRoundsWon() == 3) {
					player2->increaseSetWins();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << endl << "Player 2 has won this set, now has won " << player2->getSetsWon();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					player1->setRoundsWon(0);
					player2->setRoundsWon(0);
					setWon = true;
				}



			}

			if (player1->getSetsWon() == 7 || player2->getSetsWon() == 7) {
				gameWon = true;
		


			}
		}

		cout << "Score was" << endl;
		cout << "Player 1: " << player1->getSetsWon() << " Player 2: " << player2->getSetsWon();

}




