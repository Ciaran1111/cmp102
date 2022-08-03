#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;



class player
{
private:
	int bullsHit;
	int successRate;
	int score;
	int turns;
	string name;
	int noOfWins;
	// won flag
	bool wonRound;
	int scoreBuffer;

	int setsWon;
	int roundsWon;
	

	vector<double> scores;


public:
	// <---------- constructors/ de-constructors ---------->
	player(string, int);
	player();
	~player();

//	<----------getters / setters---------->
	int getSuccessRate();
	void setSuccessRate(int);
	int getScore();
	void setScore(int);
	int getTurns();
	void setTurns(int);
	bool getWonRound();
	void setWonRound(bool);
	int getNoWins();
	void setNoWins(int);
	string getName();
	int GetScoreBuffer();
	void setScoreBuffer(int);
	int getBullsHit();

	void setSetsWon(int);
	int getSetsWon();
	void setRoundsWon(int);
	int getRoundsWon();

	void increaseSetWins();
	void increaseRoundWins();

//	<----------Functions---------->
	int throw_bull(int);
	int throw_treble(int, int);
	int throw_double(int, int);
	int throw_single(int, int);
	

	void throw_dart();
	void take_turn(bool *RoundWon);
	void updateWins(int);
	bool check_even();

	// vector methods
	void push_score(int);
	double returnElement(int);
	int getLength();
};



