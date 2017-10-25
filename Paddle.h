#pragma once
#include "ofMain.h"

class Paddle {
public:
	float x;
	float y;
	float width;
	float height;
	ofColor color;
	Paddle();
	Paddle(float x, float y, float width, float height, ofColor color);
	void draw();
};