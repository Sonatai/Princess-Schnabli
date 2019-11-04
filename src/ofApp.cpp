#include "ofApp.h"

ofxAssimpModelLoader testEnemy;

//--------------------------------------------------------------
void ofApp::setup() {

	//... SetUP General
	ofDisableArbTex();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	cam.setDistance(200);
	cam.setPosition(0, 110, 110);
	cam.tilt(-50);
	cam.disableMouseInput();
	ofSetWindowTitle("Princess Schnably Adventure");
	ofSetColor(ofColor::white);
	ofSetSmoothLighting(true);


	/*TODO:
		1. Create all GameObjects and save in lists
		2. Spawn all GameObjects with right rotation,scale,coordinates
		3. Setup Light (using spotlight,arealight and pointlight)
	*/

	//... SetUp Skybox ...//
	background.load("skybox1.jpeg");

	//... SetUP Map ...//
	ofLoadImage(mapTex, "Map/Schnabli_Island_DefaultMaterial_AlbedoTransparency.png");
	mapModel.loadModel("Map/Schnabli_Island.obj");
	map = new Map(&mapModel);
	map->Spawn();

	//... SetUP Schnabli ...//
	ofLoadImage(schnabliTex, "Schnabli/Schnabli_DefaultMaterial_AlbedoTransparency.png");
	schnabliModelIdle.loadModel("Schnabli/Schnabli_IdleDefault.dae");
	schnabliModelIdle2.loadModel("Schnabli/Schnabli_IdleSpecial.dae");
	schnabliModelWalk.loadModel("Schnabli/Schnabli_walk.dae");

	schnabliModelIdle.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	schnabliModelIdle2.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	schnabliModelWalk.setLoopStateForAllAnimations(OF_LOOP_NONE);

	player = new Player(&schnabliModelWalk, &schnabliModelIdle, &schnabliModelIdle2);
	player->Spawn();
	player->GetPlayer()->getAnimation(0).play(); //Idle Animation

	//... SetUP Cookies ...//
	ofLoadImage(cookyTex, "Cooky/Cookie_DefaultMaterial_AlbedoTransparency.png");
	cookyModel.loadModel("Cooky/Cookie.obj");

	for (int i = 0; i < 10; i++)
		dupCookyModels[i] = cookyModel;
	for (int i = 0; i < 9; i++)
		listOfCookies[i] = new Cooky(&dupCookyModels[i]);
	listOfCookies[9] = new Cooky(&dupCookyModels[9], 3);

	SpawnCookies();

	//... SetUP Enemy ...//
	ofLoadImage(enemyTex, "Enemy/FOE_DefaultMaterial_AlbedoTransparency.png");
	enemyModel.loadModel("Enemy/FOE.obj");

	for (int i = 0; i < 3; i++)
		dupEnemyModels[i] = enemyModel;
	for (int i = 0; i < 3; i++)
		listOfEnemies[i] = new Enemy(&dupEnemyModels[i]);
	testEnemy = enemyModel;
	SpawnEnemies();

	//... SetUP Lighting ...//
	/*
	 * CutOff ca. so groß wie die Map
	 * Attenuation nicht zu klein machen sonst wird das Licht grell (benutze nur constantes)
	 * Über Concentration + Höhe die Streureichweite bestimmen
	 */
	spotlight.setSpotlight();
	spotlight.setSpotlightCutOff(80); //Wie flach/breit der Kegel ist
	spotlight.setSpotConcentration(650); //Wie weit der Kegel streut
	spotlight.setAttenuation(0.8, 0, 0); //Gesamtschwächung von Lichtenergie
	spotlight.setSpecularColor(ofColor(255, 255, 255, 50)); //... higlight reflection, dependent on the direction
	spotlight.setDiffuseColor(ofColor(255, 255, 255, 20));  //... direct light, dependent on the incident angle
	spotlight.setAmbientColor(ofColor(255, 153, 47, 50));  //... bouncing light mutiple times

	ofPushMatrix();
	spotlight.setPosition(0, 800, 0); //... Höhe bestimmt wieviel Licht überhaupt gestreut werden kann
	spotlight.setScale(4, 4, 4);
	spotlight.tiltDeg(-90);
	ofPopMatrix();

	//... Arealight
	// färbt meinen Hintergrund in dieses wunderschöne grün :)
	arealight.setAreaLight(2000, 2000);
	arealight.setSpecularColor(ofColor(64, 35, 4, 50));
	arealight.setDiffuseColor(ofColor(230, 126, 17, 20));
	arealight.setAmbientColor(ofColor(255, 140, 18, 50));

	//... Pointlight
	pointlight.setPointLight();
	pointlight.setAttenuation(0, 0.9, 0);
	pointlight.setSpecularColor(ofColor(73, 104, 191, 50));
	pointlight.setDiffuseColor(ofColor(24, 35, 64, 20));
	pointlight.setAmbientColor(ofColor(97, 139, 255, 50));

	ofPushMatrix();
	pointlight.setPosition(-6, 100, -170);
	pointlight.setScale(3, 3, 3);
	ofPopMatrix();

}

//... Zeichnet alle Cookies auf die Map
void ofApp::DrawCookies() {
	for (int i = 0; i < 10; i++) {
		if (listOfCookies[i]->alive) {
			cookyTex.bind();
			listOfCookies[i]->GetCooky()->drawFaces();
			cookyTex.unbind();
		}
	}
}

//... Setzt die richtige Position und Rotation pro Cooky
void ofApp::SpawnCookies() {

	int numRotation = listOfCookies[0]->GetCooky()->getNumRotations();
	float spawnAngle = 90.0;
	ofPoint xAxe = ofPoint(1.0, 0.0, 0.0);
	ofPoint yAxe = ofPoint(0.0, 1.0, 0.0);
	ofPoint zAxe = ofPoint(0.0, 0.0, 1.0);


	ofPoint* spawnPos = new ofPoint(-7, 4, 57);
	listOfCookies[0]->Spawn(*(spawnPos));
	listOfCookies[0]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

	spawnPos = new ofPoint(26, 4, 46);
	listOfCookies[1]->Spawn(*(spawnPos));
	listOfCookies[1]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

	spawnPos = new ofPoint(-47, 4, 60);
	listOfCookies[2]->Spawn(*(spawnPos));
	listOfCookies[2]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

	spawnPos = new ofPoint(46, 4, 15);
	listOfCookies[3]->Spawn(*(spawnPos));
	listOfCookies[3]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

	spawnPos = new ofPoint(69, 4, -62);
	listOfCookies[4]->Spawn(*(spawnPos));
	listOfCookies[4]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

	spawnPos = new ofPoint(2, 4, -62);
	listOfCookies[5]->Spawn(*(spawnPos));
	listOfCookies[5]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

	spawnPos = new ofPoint(47, 4, -8);
	listOfCookies[6]->Spawn(*(spawnPos));
	listOfCookies[6]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

	spawnPos = new ofPoint(-41, 4, 1);
	listOfCookies[7]->Spawn(*(spawnPos));
	listOfCookies[7]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

	spawnPos = new ofPoint(36, 4, -16);
	listOfCookies[8]->Spawn(*(spawnPos));
	listOfCookies[8]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

	spawnPos = new ofPoint(0, 6, 0);
	listOfCookies[9]->Spawn(*(spawnPos));
	listOfCookies[9]->GetCooky()->setScale(0.015, 0.015, 0.015);
	listOfCookies[9]->GetCooky()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);

}

//... Überprüft pro Cooky ob der Spieler nah genug ist
void ofApp::CollisionCheckCookies() {
	for (int i = 0; i < 10; i++) {
		listOfCookies[i]->CollisionCheck(player);
	}
}

//... Setzt die richtige Position und Rotation pro Enemy
void ofApp::SpawnEnemies() {
	int numRotation = listOfEnemies[0]->GetEnemy()->getNumRotations();
	float spawnAngle = 0.0;
	ofPoint* spawnPos;
	ofPoint waypoint;
	ofPoint xAxe = ofPoint(1.0, 0.0, 0.0);
	ofPoint yAxe = ofPoint(0.0, 1.0, 0.0);
	ofPoint zAxe = ofPoint(0.0, 0.0, 1.0);

	//testEnemy.setPosition(0,10,0);
	//testEnemy.setScale(0.007, 0.007, 0.007);

	//... Rechts
	ofPushMatrix();
	spawnPos = new ofPoint(11, 6, 2);
	listOfEnemies[0]->Spawn(*(spawnPos));
	spawnAngle = -90.0;
	//listOfEnemies[0]->GetEnemy()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);
	ofPopMatrix();

	//... Set waypoints:
	waypoint = ofPoint(21, 6, 2);
	listOfEnemies[0]->SetWaypoint(waypoint, 270);
	waypoint = ofPoint(37, 6, -14);
	listOfEnemies[0]->SetWaypoint(waypoint, 225);
	waypoint = ofPoint(32, 6, -19);
	listOfEnemies[0]->SetWaypoint(waypoint, 135);
	waypoint = ofPoint(25, 6, -12);
	listOfEnemies[0]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(16, 6, -12);
	listOfEnemies[0]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(13, 6, -15);
	listOfEnemies[0]->SetWaypoint(waypoint, 135);
	waypoint = ofPoint(13, 6, -23);
	listOfEnemies[0]->SetWaypoint(waypoint, 180);
	waypoint = ofPoint(20, 6, -30);
	listOfEnemies[0]->SetWaypoint(waypoint, 225);
	waypoint = ofPoint(20, 6, -58);
	listOfEnemies[0]->SetWaypoint(waypoint, 180);
	waypoint = ofPoint(16, 6, -62);
	listOfEnemies[0]->SetWaypoint(waypoint, 135);
	waypoint = ofPoint(20, 6, -66);
	listOfEnemies[0]->SetWaypoint(waypoint, 225);
	waypoint = ofPoint(65, 6, -66);
	listOfEnemies[0]->SetWaypoint(waypoint, 270);
	waypoint = ofPoint(69, 6, -62);
	listOfEnemies[0]->SetWaypoint(waypoint, 315);
	waypoint = ofPoint(65, 6, -58);
	listOfEnemies[0]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(36, 6, -58);
	listOfEnemies[0]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(31, 6, -53);
	listOfEnemies[0]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(37, 6, -47);
	listOfEnemies[0]->SetWaypoint(waypoint, 315);
	waypoint = ofPoint(65, 6, -47);
	listOfEnemies[0]->SetWaypoint(waypoint, 270);
	waypoint = ofPoint(72, 6, -40);
	listOfEnemies[0]->SetWaypoint(waypoint, 315);
	waypoint = ofPoint(72, 6, -29);
	listOfEnemies[0]->SetWaypoint(waypoint, 0);
	waypoint = ofPoint(59, 6, -16);
	listOfEnemies[0]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(59, 6, 5);
	listOfEnemies[0]->SetWaypoint(waypoint, 0);
	waypoint = ofPoint(48, 6, 16);
	listOfEnemies[0]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(41, 6, 16);
	listOfEnemies[0]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(32, 6, 25);
	listOfEnemies[0]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(62, 6, 55);
	listOfEnemies[0]->SetWaypoint(waypoint, 315);
	waypoint = ofPoint(62, 6, 64);
	listOfEnemies[0]->SetWaypoint(waypoint, 0);
	waypoint = ofPoint(54, 6, 72);
	listOfEnemies[0]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(10, 6, 72);
	listOfEnemies[0]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(0, 6, 62);
	listOfEnemies[0]->SetWaypoint(waypoint, 135);
	waypoint = ofPoint(-29, 6, 62);
	listOfEnemies[0]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(-39, 6, 72);
	listOfEnemies[0]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(-56, 6, 72);
	listOfEnemies[0]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(-67, 6, 61);
	listOfEnemies[0]->SetWaypoint(waypoint, 135);
	waypoint = ofPoint(-67, 6, 32);
	listOfEnemies[0]->SetWaypoint(waypoint, 180);
	waypoint = ofPoint(-49, 6, 14);
	listOfEnemies[0]->SetWaypoint(waypoint, 225);
	waypoint = ofPoint(-30, 6, 14);
	listOfEnemies[0]->SetWaypoint(waypoint, 270);
	waypoint = ofPoint(-18, 6, 2);
	listOfEnemies[0]->SetWaypoint(waypoint, 225);
	waypoint = ofPoint(11, 6, 2);
	listOfEnemies[0]->SetWaypoint(waypoint, 270);

	//... Mitte
	ofPushMatrix();
	spawnPos = new ofPoint(2, 6, 8);
	listOfEnemies[1]->Spawn(*(spawnPos));
	spawnAngle = -90.0;
	//listOfEnemies[1]->GetEnemy()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);
	ofPopMatrix();
	//... Set waypoints:
	waypoint = ofPoint(14, 6, 20);
	listOfEnemies[1]->SetWaypoint(waypoint, 315);
	waypoint = ofPoint(-15, 6, 49);
	listOfEnemies[1]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(-36, 6, 49);
	listOfEnemies[1]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(-40, 6, 53);
	listOfEnemies[1]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(-40, 6, 55);
	listOfEnemies[1]->SetWaypoint(waypoint, 0);
	waypoint = ofPoint(-44, 6, 59);
	listOfEnemies[1]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(-47, 6, 59);
	listOfEnemies[1]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(-55, 6, 51);
	listOfEnemies[1]->SetWaypoint(waypoint, 135);
	waypoint = ofPoint(-55, 6, 39);
	listOfEnemies[1]->SetWaypoint(waypoint, 180);
	waypoint = ofPoint(-52, 6, 36);
	listOfEnemies[1]->SetWaypoint(waypoint, 225);
	waypoint = ofPoint(-21, 6, 36);
	listOfEnemies[1]->SetWaypoint(waypoint, 270);
	waypoint = ofPoint(-15, 6, 30);
	listOfEnemies[1]->SetWaypoint(waypoint, 225);
	waypoint = ofPoint(-19, 6, 26);
	listOfEnemies[1]->SetWaypoint(waypoint, 135);
	waypoint = ofPoint(-31, 6, 26);
	listOfEnemies[1]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(-38, 6, 19);
	listOfEnemies[1]->SetWaypoint(waypoint, 135);
	//waypoint = ofPoint(-21, 6, 2);
	//listOfEnemies[1]->SetWaypoint(waypoint, 225);
	waypoint = ofPoint(-21, 6, 19);
	listOfEnemies[1]->SetWaypoint(waypoint, 270);
	waypoint = ofPoint(-21, 6, 2);
	listOfEnemies[1]->SetWaypoint(waypoint, 180);
	waypoint = ofPoint(2, 6, 3);
	listOfEnemies[1]->SetWaypoint(waypoint, 270);
	waypoint = ofPoint(2, 6, 8);
	listOfEnemies[1]->SetWaypoint(waypoint, 315);

	//... Links
	ofPushMatrix();
	spawnPos = new ofPoint(-12, 6, 0);
	listOfEnemies[2]->Spawn(*(spawnPos));
	spawnAngle = -90.0;
	//listOfEnemies[2]->GetEnemy()->setRotation(numRotation, spawnAngle, xAxe.x, xAxe.y, xAxe.z);
	ofPopMatrix();
	//... Set Waypoints
	waypoint = ofPoint(-24, 6, 0);
	listOfEnemies[2]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(-24, 6, 10);
	listOfEnemies[2]->SetWaypoint(waypoint, 0);
	waypoint = ofPoint(-27, 6, 13);
	listOfEnemies[2]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(-51, 6, 13);
	listOfEnemies[2]->SetWaypoint(waypoint, 90);
	waypoint = ofPoint(-70, 6, -7);
	listOfEnemies[2]->SetWaypoint(waypoint, 135);
	waypoint = ofPoint(-70, 6, -48);
	listOfEnemies[2]->SetWaypoint(waypoint, 180);
	waypoint = ofPoint(-48, 6, -67);
	listOfEnemies[2]->SetWaypoint(waypoint, 225);
	waypoint = ofPoint(-1, 6, -67);
	listOfEnemies[2]->SetWaypoint(waypoint, 270);
	waypoint = ofPoint(10, 6, -56);
	listOfEnemies[2]->SetWaypoint(waypoint, 315);
	waypoint = ofPoint(10, 6, -39);
	listOfEnemies[2]->SetWaypoint(waypoint, 0);
	waypoint = ofPoint(-1, 6, -27);
	listOfEnemies[2]->SetWaypoint(waypoint, 45);
	waypoint = ofPoint(-1, 6, 0);
	listOfEnemies[2]->SetWaypoint(waypoint, 0);
	waypoint = ofPoint(-12, 6, 0);
	listOfEnemies[2]->SetWaypoint(waypoint, 90);


}
//... Zeichnet alle Gegner auf die Map
void ofApp::DrawEnemies() {
	for (int i = 0; i < 3; i++) {
		enemyTex.bind();
		listOfEnemies[i]->GetEnemy()->drawFaces();
		enemyTex.unbind();
	}
	/*enemyTex.bind();
	testEnemy.drawFaces();
	enemyTex.unbind();*/
}

//--------------------------------------------------------------
void ofApp::update() {


	if (player->GetSteps() > 350) {
		for (int i = 0; i < 3; i++) {
			listOfEnemies[i]->CollisionCheck(player);
		}
	}
	if (!player->GetAlive() && !died) {
		died = true;
		player->GetPlayer()->getAnimation(0).stop();
		float angle = 180;
		ofPoint axis = ofPoint(1.0, 0.0, 0.0);
		int numRotation = player->GetPlayer()->getNumRotations();
		player->SetRotation(angle, axis, numRotation);
	}

	if (player->GetCookyCount() == 12 && !won) {
		won = true;
		player->AnimControl("WON");
	}
	player->GetPlayer()->update();
	CollisionCheckCookies();
	for (int i = 0; i < 3; i++)
		listOfEnemies[i]->WaypointControl();

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofEnableLighting();
	arealight.enable();

	glDisable(GL_DEPTH_TEST);
	background.draw(0, 0);
	glEnable(GL_DEPTH_TEST);

	spotlight.enable();
	pointlight.enable();

	cam.begin();

	mapTex.bind();
	map->GetModel()->drawFaces();
	mapTex.unbind();


	schnabliTex.bind();
	player->GetPlayer()->drawFaces();
	schnabliTex.unbind();

	DrawCookies();
	DrawEnemies();

	cam.end();
	pointlight.disable();
	spotlight.disable();
	arealight.disable();
	ofDisableLighting();

	//spotlight.draw();
	//pointlight.draw();
	//arealight.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (!died && !won) {
		float x = player->GetPlayer()->getPosition().x;
		float y = player->GetPlayer()->getPosition().y;
		float z = player->GetPlayer()->getPosition().z;
		float ms = player->GetMS();

		if (key == 'w' || key == 'W') {
			CalculateMove('v');
			player->AnimControl("WALK");
		}
		if (key == 's' || key == 'S') {
			CalculateMove('z');
			player->AnimControl("WALK");

		}
	}


}

void ofApp::CalculateMove(char direction) {
	float normMS = sqrt(pow(player->GetMS(), 2) / 2);
	float z = 0;
	float x = 0;

	if (direction == 'v') {
		switch (degState) {
		case 0:
			z = player->GetPlayer()->getPosition().z + player->GetMS();
			ofPushMatrix();
			player->GetPlayer()->setPosition(player->GetPlayer()->getPosition().x, player->GetPlayer()->getPosition().y, z);
			ofPopMatrix();
			break;
		case 315:
			z = player->GetPlayer()->getPosition().z + normMS;
			x = player->GetPlayer()->getPosition().x + normMS;
			ofPushMatrix();
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, z);
			ofPopMatrix();
			break;
		case 90:
			x = player->GetPlayer()->getPosition().x - player->GetMS();
			ofPushMatrix();
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, player->GetPlayer()->getPosition().z);
			ofPopMatrix();
			break;
		case 225:
			z = player->GetPlayer()->getPosition().z - normMS;
			x = player->GetPlayer()->getPosition().x + normMS;
			ofPushMatrix();
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, z);
			ofPopMatrix();
			break;
		case 180:
			z = player->GetPlayer()->getPosition().z - player->GetMS();
			ofPushMatrix();
			player->GetPlayer()->setPosition(player->GetPlayer()->getPosition().x, player->GetPlayer()->getPosition().y, z);
			ofPopMatrix();
			break;
		case 135:
			z = player->GetPlayer()->getPosition().z - normMS;
			x = player->GetPlayer()->getPosition().x - normMS;
			ofPushMatrix();
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, z);
			ofPopMatrix();
			break;
		case 270:
			x = player->GetPlayer()->getPosition().x + player->GetMS();
			ofPushMatrix();
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, player->GetPlayer()->getPosition().z);
			ofPopMatrix();
			break;
		case 45:
			z = player->GetPlayer()->getPosition().z + normMS;
			x = player->GetPlayer()->getPosition().x - normMS;
			ofPushMatrix();
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, z);
			ofPopMatrix();
			break;
		}

	}
	else if (direction == 'z') {
		switch (degState) {
		case 0:
			z = player->GetPlayer()->getPosition().z - player->GetMS();
			player->GetPlayer()->setPosition(player->GetPlayer()->getPosition().x, player->GetPlayer()->getPosition().y, z);
			break;
		case 315:
			z = player->GetPlayer()->getPosition().z - normMS;
			x = player->GetPlayer()->getPosition().x - normMS;
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, z);
			break;
		case 90:
			x = player->GetPlayer()->getPosition().x + player->GetMS();
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, player->GetPlayer()->getPosition().z);
			break;
		case 225:
			z = player->GetPlayer()->getPosition().z + normMS;
			x = player->GetPlayer()->getPosition().x - normMS;
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, z);
			break;
		case 180:
			z = player->GetPlayer()->getPosition().z + player->GetMS();
			player->GetPlayer()->setPosition(player->GetPlayer()->getPosition().x, player->GetPlayer()->getPosition().y, z);
			break;
		case 135:
			z = player->GetPlayer()->getPosition().z + normMS;
			x = player->GetPlayer()->getPosition().x + normMS;
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, z);
			break;
		case 270:
			x = player->GetPlayer()->getPosition().x - player->GetMS();
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, player->GetPlayer()->getPosition().z);
			break;
		case 45:
			z = player->GetPlayer()->getPosition().z - normMS;
			x = player->GetPlayer()->getPosition().x + normMS;
			player->GetPlayer()->setPosition(x, player->GetPlayer()->getPosition().y, z);
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (!died && !won) {
		if (key == 'd' || key == 'D') {

			float angle = 45;
			ofPoint axis = ofPoint(0.0, 0.0, 1.0);
			int numRotation = player->GetPlayer()->getNumRotations();
			player->SetRotation(angle, axis, numRotation);
			degState += 45;
			if (degState > 315) degState = 0;

		}
		if (key == 'a' || key == 'A') {

			float angle = -45;
			ofPoint axis = ofPoint(0.0, 0.0, 1.0);
			int numRotation = player->GetPlayer()->getNumRotations();
			player->SetRotation(angle, axis, numRotation);
			degState -= 45;
			if (degState < 0) degState = 315;

		}

		if (key == ' ')
			player->AnimControl("IDLE2");
		else
			player->AnimControl("IDLE");
	}
	if (key == 'i') {
		cout << "Enemy 1 State: " << listOfEnemies[0]->state << endl;
		cout << "Enemy 1 Position: " << listOfEnemies[0]->GetEnemy()->getPosition().x
			<< " / " << listOfEnemies[0]->GetEnemy()->getPosition().y << " / "
			<< listOfEnemies[0]->GetEnemy()->getPosition().z << endl;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	/*cout << "Player Position: " << player->GetPlayer()->getPosition().x
		<< " / " << player->GetPlayer()->getPosition().y
		<< " / " <<  player->GetPlayer()->getPosition().z << endl;*/
	player->AnimControl("IDLE2");
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
