#pragma once
#include "ofxAssimpModelLoader.h"

class Map 
{
private:
	ofxAssimpModelLoader* model;
public:
	Map();
	Map(ofxAssimpModelLoader* model);
	~Map();
	void Spawn();
	ofxAssimpModelLoader* GetModel();
};

