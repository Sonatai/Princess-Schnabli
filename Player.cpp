#include "Player.h"



Player::Player()
{
}

Player::Player(ofxAssimpModelLoader* move, ofxAssimpModelLoader* idle, ofxAssimpModelLoader* idle2) {
	model[0] = move;
	model[1] = idle;
	model[2] = idle2;
	currentPlayer = model[1];

}

Player::~Player()
{
}

void Player::Spawn() {

	//... model 0 rotation
	float angle = 90.0;
	int numRotation = model[0]-> getNumRotations();
	ofPoint axis = ofPoint(1.0, 0.0, 0.0);
	model[0]-> setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	angle = 180.0;
	numRotation = model[0]->getNumRotations();
	axis = ofPoint(0.0, 1.0, 0.0);
	model[0]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	angle = 180.0;
	numRotation = model[0]->getNumRotations();
	axis = ofPoint(0.0, 0.0, 1.0);
	model[0]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	//... model 1 rotation
	angle = 90.0;
	numRotation = model[1]->getNumRotations();
	axis = ofPoint(1.0, 0.0, 0.0);
	model[1]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	angle = 180.0;
	numRotation = model[1]->getNumRotations();
	axis = ofPoint(0.0, 1.0, 0.0);
	model[1]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	angle = 180.0;
	numRotation = model[1]->getNumRotations();
	axis = ofPoint(0.0, 0.0, 1.0);
	model[1]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	//... model 2 rotation
	angle = 90.0;
	numRotation = model[2]->getNumRotations();
	axis = ofPoint(1.0, 0.0, 0.0);
	model[2]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	angle = 180.0;
	numRotation = model[2]->getNumRotations();
	axis = ofPoint(0.0, 1.0, 0.0);
	model[2]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	angle = 180.0;
	numRotation = model[2]->getNumRotations();
	axis = ofPoint(0.0, 0.0, 1.0);
	model[2]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);


	//... set scale
	model[0] ->setScale(0.025f, 0.025f, 0.025f);
	model[1]->setScale(0.025f, 0.025f, 0.025f);
	model[2] ->setScale(0.025f, 0.025f, 0.025f);

	//... 5
	currentPlayer->setPosition(-65, 5, 65);

}

void Player::AnimControl(std::string state) {
	this -> state = state;

	if (state == "IDLE") {
		if (currentPlayer == model[0]) {
			currentPlayer->getAnimation(0).stop();
			int x = currentPlayer->getPosition().x;
			int y = currentPlayer->getPosition().y;
			int z = currentPlayer->getPosition().z;

			model[1]->setPosition(x, y, z);
			currentPlayer = model[1];
		}

		if (currentPlayer->getAnimation(0).isFinished()) {
			currentPlayer->getAnimation(0).play();
		}
	}

	if (state == "WALK") {
		steps+=ms;
		if (currentPlayer != model[0]) {
			currentPlayer->getAnimation(0).stop();
			int x = currentPlayer->getPosition().x;
			int y = currentPlayer->getPosition().y;
			int z = currentPlayer->getPosition().z;

			model[0]->setPosition(x, y, z);
			currentPlayer = model[0];
		}
		currentPlayer->getAnimation(0).play();
		
	}

	if (state == "IDLE2") {
		if (currentPlayer == model[1]) {
			currentPlayer->getAnimation(0).stop();
			int x = currentPlayer->getPosition().x;
			int y = currentPlayer->getPosition().y;
			int z = currentPlayer->getPosition().z;

			model[2]->setPosition(x, y, z);
			currentPlayer = model[2];
			currentPlayer->getAnimation(0).play();
		}
	}
	
	if (state == "WON") {
		currentPlayer->getAnimation(0).stop();
		int x = currentPlayer->getPosition().x;
		int y = currentPlayer->getPosition().y;
		int z = currentPlayer->getPosition().z;

		model[2]->setPosition(x, y, z);
		currentPlayer = model[2];
		currentPlayer->getAnimation(0).play();
	}
}

ofxAssimpModelLoader* Player::GetPlayer() {
	return currentPlayer;
}

float Player::GetMS() {
	return ms;
}

void Player::SetRotation(float angle, ofPoint axis, int numRotation) {

	ofPushMatrix();
	model[0]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
	model[1]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
	model[2]->setRotation(numRotation, angle, axis.x, axis.y, axis.z);
	ofPopMatrix();
}

int Player::GetHP() {
	return hp;
}
int Player::GetCookyCount() {
	return cookyCount;
}
void Player::SetHP() {
	if (hp > 1) {
		hp--;
	}
	else {
		hp--;
		alive = false;
	}
}
void Player::SetCookyCount(int value) {
	cookyCount += value;
}

void Player::ResetSteps() {
	steps = 0;
}
float Player::GetSteps() {
	return steps;
}

bool Player::GetAlive() {
	return alive;
}