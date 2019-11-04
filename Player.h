#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"

class Player
{
private:
	ofxAssimpModelLoader* model[3];
	ofxAssimpModelLoader* currentPlayer;
	std::string state = "IDLE"; //IDLE IDLE2 WALK
	int hp = 3;
	int cookyCount = 0;
	float ms = 0.5;
	float steps = 0;
	bool alive = true;

public:
	Player();
	Player(ofxAssimpModelLoader* move, ofxAssimpModelLoader* idle, ofxAssimpModelLoader* idle2);
	~Player();

	//... Setup Player
	void Spawn();
	//... Control Animation of Player
	void AnimControl(std::string state);
	//... return the model
	ofxAssimpModelLoader* GetPlayer();
	//... return movementspeed
	float GetMS();
	void SetRotation(float angle, ofPoint axis, int numRotation);
	int GetHP();
	int GetCookyCount();
	void SetHP();
	void SetCookyCount(int value);
	//... Reset Step to 0
	void ResetSteps();
	float GetSteps();
	bool GetAlive();
};

