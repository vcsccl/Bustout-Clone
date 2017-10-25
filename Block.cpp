#include "Block.h"
#include "ofMain.h"

Block::Block() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	color = ofColor(0);
	points = 0;
}

Block::Block(int x, int y, int w, int h, char kind) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	if (kind == 'r') {
		this->points = 1;
		this->color = ofColor(250, 50, 50);
	}
	else if (kind == 'g') {
		this->points = 2;
		this->color = ofColor(50, 250, 50);
	}
	else if (kind == 'b') {
		this->points = 4;
		this->color = ofColor(50, 50, 250);
	}
	if (kind == 'o') {
		this->points = 8;
		this->color = ofColor(255, 165, 0);
	}
	else if (kind == 'y') {
		this->points = 16;
		this->color = ofColor(255, 255, 0);
	}
	else if (kind == 'p') {
		this->points = 32;
		this->color = ofColor(160, 32, 240);
	}
	this->destroyed = false;
}

void Block::draw() {
	if (!destroyed) {
		ofSetColor(color);
		ofDrawRectangle(x, y, w, h);
	}
}