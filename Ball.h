#pragma once
#include "ofMain.h"
#include "Block.h"

class Ball {
public:
	ofVec2f location;
	ofVec2f velocity;
	ofVec2f acceleration;
	float size;
	ofColor color;
	Ball();
	Ball(ofVec2f location, ofVec2f velocity, ofVec2f acceleration, float size, ofColor color);
	void draw();
	void move();
	void applyForce(ofVec2f force);
	void bounce(int paddleX, int level, ofSoundPlayer bumperSound);
	void offScreen(int livesLeft);
	bool hits(int x, int y, string row);
	void reset();
};