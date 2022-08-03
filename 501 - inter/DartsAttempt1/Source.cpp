#include <iostream>
#include "player.h"
#include "game.h"
#include <vector>
#include <time.h>
#include "interactivePlayer.h"



int main() {
//	<----------Object Initalisation---------->
player* player1 = new player("joe", 71);
player* player2 = new player("sid", 73);

interactivePlayer* playerInteract = new interactivePlayer();

playerInteract->setSuccessRate(100);
game* game1 = new game();

int noGames = 0;
srand(time(NULL)); // seeding random number generator 


// setting scores to 501
player1->setScore(501);  
player2->setScore(501);

// taking input for how what type of game they wish to play
cout << "Welcome to the darts simulation!" << endl;
cout << "Enter 1 for Joe vs Sid, Enter 2 for to play in the world championship(Interactive)" << endl;
int gameType = 0;
cin >> gameType;

// switch statement to determin the desired gamemode 
switch (gameType)
{
	case 1:
		cout << "Now enter how many games you wish to simulate" << endl; // takes in how many simulations is to be ran
		cin >> noGames;
	
		game1->PlayGame(player1, player2, noGames); // calls playGame function and passes in pointers to player objects and noGames variable by value
		cout << endl << noGames << " Simulated games over" << endl; 
		break;

	case 2:
		cout << "What is your accuracy? " << endl;
		int userSuccess = 0;
		cin >> userSuccess;
		playerInteract->setSuccessRate(userSuccess);
		// calls interactive game function from game object passing in 2 pointers to objects
		game1->playInteractiveGame(playerInteract, player1);
		break;
}

	// function counts occurances to work out how many games ended in 7:4 for example
	game1->countScores(player1, noGames);
	game1->countScores(player2, noGames);

	// outputs relevant scores
	game1->outputScores(noGames, player1, player2);



	delete player1;
	delete player2;
}