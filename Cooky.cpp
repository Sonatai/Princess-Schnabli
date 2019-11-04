#include "Cooky.h"



Cooky::Cooky()
{
}

Cooky::Cooky(ofxAssimpModelLoader* model)
{
	cooky = model;
}

Cooky::Cooky(ofxAssimpModelLoader* model,int value)
{
	cooky = model;
	this->value = value;
}

Cooky::~Cooky()
{
}

void Cooky::CollisionCheck(Player* player) {
	int xDistance = (unsigned)((unsigned int)player->GetPlayer()->getPosition().x - (unsigned int)cooky->getPosition().x);
	int zDistance = (unsigned)((unsigned int)player->GetPlayer()->getPosition().z - (unsigned int)cooky->getPosition().z);

	if (xDistance >= 0 && xDistance <= 8 &&
		zDistance >= 0 && zDistance <= 8 
		&& alive) {
		alive = false;
		player->SetCookyCount(this->value);
		std::cout << "Cooky Count: " << player->GetCookyCount() << std::endl;
	}
}

void Cooky::Spawn(ofPoint pos) {
	cooky->setScale(0.009f, 0.009f, 0.009f);
	cooky->setPosition(pos.x, pos.y, pos.z);
}

ofxAssimpModelLoader* Cooky::GetCooky() {
	return cooky;
}

