#include "ofApp.h"
#include "ofMain.h"
#include "Block.h"

void ofApp::setup() {
	ofSetFullscreen(true);
	ofSetBackgroundColor(25);
	ofHideCursor();
	powerupImage.load("powerup.png");
	loadFont();
	loadSound();
	mainPaddle = new Paddle(ofGetWidth() / 2, ofGetHeight() - 100, 200, 50, ofColor(200));
	mainBall = new Ball(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2), ofVec2f(2, 2), ofVec2f(0, 0), 50, ofColor(200));
}

void ofApp::update() {
	if (gameState == GAME_SCREEN) {
		mainBall->move();
		mainBall->bounce(mainPaddle->x, level, bumperSound);
		mainBall->offScreen(livesLeft);
		destroyBrickLogic();
		powerupLogic();
		if (bonusBall != NULL) {
			bonusBall->move();
			bonusBall->bounce(mainPaddle->x, level, bumperSound);
			if (bonusBall->location.y > ofGetScreenHeight()) {
				delete bonusBall;
				bonusBall = NULL;
			}
		}
		if (livesLeft < 0) gameState = GAME_OVER_SCREEN;
		if (level > 5) gameState = WIN_SCREEN;
	}
}

void ofApp::draw(){
	if (gameState == START_SCREEN) {
		drawStartScreen();
	}
	else if (gameState == GAME_SCREEN) {
		drawGameScreen();
	}
	else if (gameState == GAME_OVER_SCREEN) {
		drawGameOverScreen();
	}
	else if (gameState == WIN_SCREEN) {
		drawWinScreen();
	}
}

void ofApp::drawStartScreen() {
	font1.drawString("Bustout", 150, 200);
	font2.drawString("Enter Key to Select Level", 150, 300);
	font3.drawString("1: Easy", 150, 350);
	font3.drawString("2: Moderate", 150, 400);
	font3.drawString("3: Difficult", 150, 450);
	font3.drawString("4: Ultra", 150, 500);
	font3.drawString("5: Impossible", 150, 550);
}

void ofApp::drawGameScreen() {
	ofSetColor(255);
	font3.drawString("SCORE: " + ofToString(score), 30, 30);
	mainPaddle->draw();
	mainBall->draw();
	drawLives();
	if (mainPowerup != NULL) mainPowerup->draw(powerupImage);
	if (bonusBall != NULL) bonusBall->draw();
	for (int i = 0; i < blocks.size(); i++) {
		blocks.at(i)->draw();
	}
}

void ofApp::drawGameOverScreen() {
	ofSetColor(255);
	font2.drawString("GAME OVER", 150, 300);
	font3.drawString("SCORE: " + ofToString(score), 150, 350);
	font3.drawString("Press any key to continue", 150, 550);
}

void ofApp::drawWinScreen() {
	ofSetColor(255);
	font2.drawString("YOU WIN!", 150, 300);
	font3.drawString("SCORE: " + ofToString(score), 150, 350);
	font3.drawString("Press any key to continue", 150, 550);
}

void ofApp::drawLives() {
	for (int i = 0; i < livesLeft; i++) {
		ofDrawCircle(ofGetWidth() - 150 + (i * 30), 30, 15);
	}
}

void ofApp::loadFont() {
	font1.loadFont("font.ttf", 200);
	font2.loadFont("font.ttf", 50);
	font3.loadFont("font.ttf", 25);
}

void ofApp::loadSound() {
	gameOverSound.load("gameOverSound.mp3");
	bumperSound.load("bumperSound.mp3");
	blockSoundR.load("blockSoundR.mp3");
	blockSoundG.load("blockSoundG.mp3");
	blockSoundB.load("blockSoundB.mp3");
	playerWinSound.load("playerWinSound.mp3");
	bumperSound.setSpeed(1.5);
	blockSoundR.setSpeed(2);
	blockSoundG.setSpeed(3);
	blockSoundB.setSpeed(4);
}

void ofApp::keyPressed(int key){
	if (gameState == START_SCREEN) {
		if (key >= '1' && key <= '5') {
			level = key - 48;
		}
		prepareLevel(level);
		gameState = GAME_SCREEN;
		mainPaddle->width = 500 / level;
		mainBall->velocity = ofVec2f(level, level);
	}
	if (gameState == GAME_OVER_SCREEN || gameState == WIN_SCREEN) {
		gameState = START_SCREEN;
		score = 0; 
		livesLeft = 4;
		level = 0;
	}
}

void ofApp::prepareLevel(int level) {
	blocks.clear();
	vector<string> lines;
	ofBuffer buffer = ofBufferFromFile(ofToString(level) + ".txt");
	for (auto line : buffer.getLines()) {
		lines.push_back(line);
	}
	for (int i = 0; i < lines.size(); i++) {
		row = lines[i];
		for (int j = 0; j < row.size(); j++) {
			char code = row[j];
			if (code == ' ') continue;
			Block *b = new Block(j * ofGetWidth() / row.size(), 50 + (i * 55), ofGetWidth() / row.size(), 50, code);
			blocks.push_back(b);
		}
	}
}

void ofApp::destroyBrickLogic() {
	for (int i = 0; i < blocks.size(); i++) {
		if (!blocks.at(i)->destroyed && (mainBall->hits(blocks.at(i)->x, blocks.at(i)->y, row) || (bonusBall != NULL && bonusBall->hits(blocks.at(i)->x, blocks.at(i)->y, row)))) {
			if (blocks.at(i)->points == 1) {
				blockSoundR.play();
				mainBall->velocity *= -1;
			}
			if (blocks.at(i)->points == 2) {
				blockSoundG.play();
				mainBall->velocity *= -1.01;
			}
			if (blocks.at(i)->points == 4) {
				blockSoundB.play();
				mainBall->velocity *= -1.02;
			}
			if (blocks.at(i)->points == 8) {
				blockSoundR.play();
				mainBall->velocity *= -1.03;
			}
			if (blocks.at(i)->points == 16) {
				blockSoundG.play();
				mainBall->velocity *= -1.04;
			}
			if (blocks.at(i)->points == 32) {
				blockSoundB.play();
				mainBall->velocity *= -1.05;
				if (mainPowerup == NULL && bonusBall == NULL) {
					mainPowerup = new Powerup(ofVec2f(blocks.at(i)->x, blocks.at(i)->y), ofVec2f(1, 1), 0, 70, 70);
				}
			}
			blocks.at(i)->destroyed = true;
			score += blocks.at(i)->points;
			allDestroyed++;
			allBlocksCleared = false;
		}
	}
	if (blocks.size() == allDestroyed) {
		allBlocksCleared = true;
		allDestroyed = 0;
	}
	if (allBlocksCleared) {
		playerWinSound.play();
		mainPaddle->width = 500 / level;
		mainBall->velocity = ofVec2f(level, level);
		livesLeft = 4;
		++level;
		prepareLevel(level);
	}
}

void ofApp::powerupLogic() {
	if (mainPowerup != NULL) {
		mainPowerup->move();
		if (mainPowerup->offScreen()) {
			delete mainPowerup;
			mainPowerup = NULL;
		}
		if (mainPowerup->hitsPaddle(mainPaddle->x, level)) {
			delete mainPowerup;
			mainPowerup = NULL;
			bonusBall = new Ball(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2), ofVec2f(2, 2), ofVec2f(0, 0), 50, ofColor(200));
		}
	}
}

void ofApp::keyReleased(int key) {

}

void ofApp::mouseMoved(int x, int y ){
	 mainPaddle->x = x - 100;
	 //if (gameState == GA<E_SCREEN) mainPaddle->x = x - (250 / level);
}


void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button) {

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}


void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
