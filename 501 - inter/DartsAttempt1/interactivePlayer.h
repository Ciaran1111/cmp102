#pragma once
#include "player.h"
#include <iostream>
using namespace std;

class interactivePlayer :
    public player
{
public:
   
    interactivePlayer();

    void aimAndThrow(bool*);
    void DeductPoints(int);

};

