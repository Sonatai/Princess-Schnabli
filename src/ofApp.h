#pragma once

#include <iostream>
#include "ofxAssimpModelLoader.h"
#include "ofMain.h"
#include "../Map.h"
#include "../Player.h"
#include "../Cooky.h"
#include "../Enemy.h"

class ofApp : public ofBaseApp {
private:
	ofEasyCam cam;
	ofImage background;

	int degState = 180;
	bool died = false;
	bool won = false;

	//... UI

	//... Lichtquellen
	ofLight spotlight;
	ofLight arealight;
	ofLight pointlight;

	//... Models and Textures
	ofxAssimpModelLoader mapModel;
	ofTexture mapTex;
	Map* map;

	ofxAssimpModelLoader schnabliModelIdle;
	ofxAssimpModelLoader schnabliModelIdle2;
	ofxAssimpModelLoader schnabliModelWalk;
	ofTexture schnabliTex;
	Player* player;

	ofxAssimpModelLoader cookyModel;
	ofTexture cookyTex;
	Cooky* listOfCookies[10];
	ofxAssimpModelLoader dupCookyModels[10];

	ofxAssimpModelLoader enemyModel;
	ofTexture enemyTex;
	Enemy* listOfEnemies[3];
	ofxAssimpModelLoader dupEnemyModels[3];

public:
	//... Does translate for player
	void CalculateMove(char direction);
	void DrawCookies();
	void SpawnCookies();
	void CollisionCheckCookies();
	void SpawnEnemies();
	void DrawEnemies();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

};
