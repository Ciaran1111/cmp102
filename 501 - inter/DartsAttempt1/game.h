#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "interactivePlayer.h"
using namespace std;

class game
{
private:
	vector<double> gameLengths;
	double ScoreCount[2][7];
public:
// <---------- constructors/ de-constructors ---------->
	game();
	~game();



	void updateList(player*);
	void countScores(player*, int);
	double findmax();
	double countOccurances(int);
	int decideFirst(player*, player*);
	int workDif(int);




	



	void outputScores(int, player*, player*);



	void PlayGame(player*, player*, int);
	void playInteractiveGame(interactivePlayer*, player*);
};



