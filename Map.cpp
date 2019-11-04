#include "Map.h"



Map::Map()
{
}

Map::Map(ofxAssimpModelLoader* model) {
	this->model = model;
}

Map::~Map()
{
}

void Map::Spawn() {
	float angle = 180.0;
	ofPoint axis = ofPoint(1.0, 0.0, 0.0);
	int numRotation = model -> getNumRotations();
	model -> setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	angle = 180.0;
	numRotation = model->getNumRotations();
	axis = ofPoint(0.0, 1.0, 0.0);
	model->setRotation(numRotation, angle, axis.x, axis.y, axis.z);

	model -> setScale(0.3, 0.3, 0.3);
	model->setPosition(0, 0, 0);
}

ofxAssimpModelLoader* Map::GetModel() {
	return model;
}
