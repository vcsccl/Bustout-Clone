#include "Paddle.h"
#include "ofMain.h"

Paddle::Paddle() {
	x = ofGetWidth() / 2;
	y = ofGetHeight() - 50;
	width = 200;
	height = 50;
	color = ofColor(255);
}

Paddle::Paddle(float x, float y, float width, float height, ofColor color) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->color = color;
}

void Paddle::draw() {
	ofSetColor(color);
	ofDrawRectangle(x, y, width, height);
}
