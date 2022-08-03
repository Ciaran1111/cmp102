#include "player.h"
#include <iostream>
#include <string>
#include "game.h"
#include <time.h>
using namespace std;

// <---------- constructors/ de-constructors ---------->
player::player(string name, int successRate) {
	this->name = name;
	this->successRate = successRate;
	this->wonRound = false;
	this->turns = 0;
	this->noOfWins = 0;
	this->bullsHit = 0;
	this->roundsWon = 0;
	this->setsWon = 0;
} 
// default constructor
player::player() {
	
	this->score = 0;
	this->scoreBuffer = 0;
	this->successRate = 0;
	this->wonRound = false;
	this->turns = 0;
	this->noOfWins = 0;
	this->bullsHit = 0;
	this->roundsWon = 0;
	this->setsWon = 0;


}
player::~player() {

};
// <---------- getters/setters ---------->
int player::getSuccessRate() {
	return successRate;
}
void player::setSuccessRate(int successRate) {
	this->successRate = successRate;
}
int player::getScore() {
	return score;
}
void player::setScore(int score) {
	this->score = score;
}
string player::getName() {
	return name;
}

void player::setWonRound(bool won) {
	this->wonRound = won;
}
bool player::getWonRound() {
	return wonRound;
}
int player::getNoWins() {
	return noOfWins;
}
void player::setNoWins(int noOfwins) {
	this->noOfWins = noOfWins;
}
void player::updateWins(int newWin) {
	noOfWins = noOfWins + noOfWins;
}

int player::GetScoreBuffer() {
	return scoreBuffer;
}

void player::setScoreBuffer(int newBuf) {
	this->scoreBuffer = newBuf;
}


void player::setTurns(int turns) {
	this->turns = turns;
}
int player::getTurns() {
	return turns;
}
int player::getBullsHit() {
	return bullsHit;
}

void player::setRoundsWon(int rounds) {
	this->roundsWon = rounds;
}

void player::setSetsWon(int sets) {
	this->setsWon = sets;
}
int player::getRoundsWon() {
	return roundsWon;
}
int player::getSetsWon() {
	return setsWon;
}

void player::increaseSetWins() {
	setsWon++;
}
void player::increaseRoundWins() {
	roundsWon++;
}

double player::returnElement(int i) {
	return scores[i];
}

void player::push_score(int score) {
	scores.push_back(score);
}
int player::getLength() {
	return scores.size();
}

// <---------- Functions ---------->

int player::throw_bull(int percentage) {

	//  Throw for the bull with percent accuracy (20<p<85)
//	srand(time(NULL));
	int random = rand() % 100 + 1;

	if (random <= (percentage - 20))
	{
	    bullsHit++;
		return 50;
		
	}
	else if (random <= 85)
	{
		return 25;
	}
	else
	{
		return rand() % 20 + 1;
	}
}
int player::throw_treble(int d, int p) {

	//  return result of throwing for treble d with accuracy p%  (o<90)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	//srand(time(NULL));
	int r = rand() % 100 + 1;

	if (r <= p)
		return 3 * d;
	else if (r <= 90)
		return d;
	else if (r <= 93)
		return 3 * bd[0][d];
	else if (r <= 96)
		return 3 * bd[1][d];
	else if (r <= 98)
		return bd[0][d];
	else
		return bd[1][d];
}

int player::throw_double(int d, int accuracy) {

	//  return result of throwing for double d with accuracy 80%

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	//srand(time(NULL));
	int r = rand() % 100 + 1;

	if (r <= accuracy)
		return 2 * d;
	else if (r <= accuracy + 5)
		return 0;
	else if (r <= accuracy + 10)
		return d;
	else if (r <= accuracy + 13)
		return 2 * bd[0][d];
	else if (r <= accuracy + 16)
		return 2 * bd[1][d];
	else if (r <= accuracy + 18)
		return bd[0][d];
	else
		return bd[1][d];
}

int player::throw_single(int d, int accuracy) {

	//  return result of throwing for single d with accuracy 88% (or 80% for the outer bullseye)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	//srand(time(NULL));
	int r = rand() % 100 + 1;

	if (d == 25) {		// outer bullseye has success rate of 80%
		if (r <= accuracy) // if the random number is less than success rate accuacy then return outer bool (25)
			return 25;
		else if (r <= accuracy + 10) {
			bullsHit++;
			return 50;
			
		}
		else 
			return rand() % 20 + 1; // if a miss, return a random score
		
	}
	else			// we must be aiming for 1 to 20 single
		if (r <= accuracy)
			return d;
		else if (r <= accuracy + 4)
			return bd[0][d];
		else if (r <= accuracy + 8)
			return bd[1][d];
		else if (r <= accuracy + 10)
			return 3 * d;
		else
			return 2 * d;
}

bool player::check_even() {
	if (score % 2 == 0) {
		return true;
	}
	else {
		return false;
	}
}

// function to decide throw
void player::throw_dart() {

	if (score == 0) {
		// do nothing
		return;
 	}

	if (score >= 62) {   // if score >=62 then throw treble 20
		score =  score - throw_treble(20, successRate);
		turns++;
	}
	else if (score >50) { // throw to try get to a score of 50 if the score is > 50 and < 62
		score = score - throw_single(score - 50, successRate);
		turns++;
		if (score == 1 || score < 0) {
			score = GetScoreBuffer();
		}
	}
	else if (score == 50) {  // throw bull if score = 50
		int valueHit = throw_bull(successRate);
		score = score - valueHit;
		turns++;
		if (valueHit != 50 && score < 2) {
			score = GetScoreBuffer();
		}

	}
	else if (score > 40 && (score - 2) % 3 == 0) {
		// if score - 2 / 3 has a remainder = 0 then throw treble of score / 3 ensuring the game will end a double.	
			score = score - throw_treble(score / 3, successRate);
			turns++;

	}
	else if (check_even() && (score / 2) <=20) {
		
		score = score - throw_double((score / 2), successRate);
		turns++;

		// retrieve old score if bust 
		if (score == 1 || score < 0) {
			score = GetScoreBuffer();
		}
		
	}
	else if (!check_even() || (score / 2) > 20) {
		

		score = score - throw_single(1, successRate);
		turns++;
		// retrieve old score if bust
		if (score == 1 || score < 0) {
			score = GetScoreBuffer();
		}
	}

	// if score = 0 then round won
	if (score == 0) {
		wonRound = true;		
	}
}

void player::take_turn(bool *RoundWon) {
	int i = 0;
	// used to retrieve old score if goes under 0 (
	setScoreBuffer(score);

	while (i < 3 && score != 0) {
		// throws a single dart
		throw_dart();
	//	cout  << name << " Score is " << score << endl;

		
		if (score == 0) {
			// sets the variable that roundWon points to, to true
			*RoundWon = true;
			roundsWon++; // incrementing rounds won
			return;
		}

		i++;
	}
	//cout << endl;

}

