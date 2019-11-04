#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"
#include "Player.h"


class Cooky
{
private:
	ofxAssimpModelLoader* cooky;
	int value = 1;
	

public:
	bool alive = true;
	Cooky();
	Cooky(ofxAssimpModelLoader* model);
	Cooky(ofxAssimpModelLoader* model, int value);
	~Cooky();
	void CollisionCheck(Player* player);
	void Spawn(ofPoint pos);
	ofxAssimpModelLoader* GetCooky();
};
 
