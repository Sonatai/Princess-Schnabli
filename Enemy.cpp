#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::Enemy(ofxAssimpModelLoader* model)
{
	enemy = model;
}

Enemy::~Enemy()
{
}

void Enemy::CollisionCheck(Player* player){
	int xDistance = (unsigned)((unsigned int)player->GetPlayer()->getPosition().x - (unsigned int)enemy->getPosition().x);
	int zDistance = (unsigned)((unsigned int)player->GetPlayer()->getPosition().z - (unsigned int)enemy->getPosition().z);

	if (xDistance >= 0 && xDistance <= 6 &&
		zDistance >= 0 && zDistance <= 6) {
		player->SetHP();
		player->ResetSteps();
		std::cout << "Player HP: " << player->GetHP() << std::endl;
	}
}
void Enemy::Spawn(ofPoint pos){
	enemy -> setScale(0.007, 0.007, 0.007);
	enemy->setPosition(pos.x, pos.y, pos.z);
}
ofxAssimpModelLoader* Enemy::GetEnemy() {
	return enemy;
}

void Enemy::SetWaypoint(ofPoint point, int deg) {
	waypoints[wNum] = point;
	waydeg[wNum] = deg;
	wNum++;
}

void Enemy::WaypointControl() {
	if (state == "IDLE") {
		if (wNum > 0) {
			index++;
			state = "WALK";
		}
	}

	if (state == "WALK") {
		int xDistance = (unsigned)((unsigned int)waypoints[index].x - (unsigned int)enemy->getPosition().x);
		int zDistance = (unsigned)((unsigned int)waypoints[index].z - (unsigned int)enemy->getPosition().z);

		if ((xDistance == 0 || xDistance == 1) && (zDistance == 0 || zDistance == 1 )) {
			if (index == wNum - 1) {
				index = 0;
			} else { 
				index++; 
			}
			state == "IDLE";
		}
		else {
			CalculateMove();
		}
	}

}

void Enemy::CalculateMove() {
	float normMS = sqrt(pow(ms, 2) / 2);
	float z = 0;
	float x = 0;

		switch (waydeg[index]) {
		case 0:
			z = enemy->getPosition().z + ms;
			ofPushMatrix();
			enemy->setPosition(enemy->getPosition().x, enemy->getPosition().y, z);
			ofPopMatrix();
			break;
		case 315:
			z = enemy->getPosition().z + normMS;
			x = enemy->getPosition().x + normMS;
			ofPushMatrix();
			enemy->setPosition(x, enemy->getPosition().y, z);
			ofPopMatrix();
			break;
		case 90:
			x = enemy->getPosition().x - ms;
			ofPushMatrix();
			enemy->setPosition(x, enemy->getPosition().y, enemy->getPosition().z);
			ofPopMatrix();
			break;
		case 225:
			z = enemy->getPosition().z - normMS;
			x = enemy->getPosition().x + normMS;
			ofPushMatrix();
			enemy->setPosition(x, enemy->getPosition().y, z);
			ofPopMatrix();
			break;
		case 180:
			z = enemy->getPosition().z - ms;
			ofPushMatrix();
			enemy->setPosition(enemy->getPosition().x, enemy->getPosition().y, z);
			ofPopMatrix();
			break;
		case 135:
			z =enemy->getPosition().z - normMS;
			x = enemy->getPosition().x - normMS;
			ofPushMatrix();
			enemy->setPosition(x, enemy->getPosition().y, z);
			ofPopMatrix();
			break;
		case 270:
			x = enemy->getPosition().x + ms;
			ofPushMatrix();
			enemy->setPosition(x, enemy->getPosition().y, enemy->getPosition().z);
			ofPopMatrix();
			break;
		case 45:
			z = enemy->getPosition().z + normMS;
			x = enemy->getPosition().x - normMS;
			ofPushMatrix();
			enemy->setPosition(x, enemy->getPosition().y, z);
			ofPopMatrix();
			break;
		}

	
}