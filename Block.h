#pragma once
#include "ofMain.h"

class Block{
public:
	int x;
	int y;
	int w;
	int h;
	ofColor color;
	int points;
	bool destroyed;
	Block();
	Block(int x, int y, int w, int h, char kind);
	void draw();
};