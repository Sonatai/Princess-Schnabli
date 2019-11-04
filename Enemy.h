#pragma once
#include <iostream>
#include "ofxAssimpModelLoader.h"
#include "Player.h"

class Enemy
{
private:
	ofxAssimpModelLoader* enemy;
	ofPoint waypoints[100];
	int waydeg[100];
	int wNum = 0;
	int index = -1;
	
	float ms = 0.1;

public:
	std::string state = "IDLE";
	Enemy();
	Enemy(ofxAssimpModelLoader* model);
	~Enemy();
	//... Check if Player have same x and z coord
	void CollisionCheck(Player* player);
	//... Set up enemy
	void Spawn(ofPoint pos);
	//... return model
	ofxAssimpModelLoader* GetEnemy();
	//... Set a new waypoint
	void SetWaypoint(ofPoint point, int deg);
	//... Controller of the waypoints / little bit buggy
	void WaypointControl();
	//... Does the translate of the enemy
	void CalculateMove();
};

