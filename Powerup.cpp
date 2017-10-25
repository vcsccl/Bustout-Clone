#include "ofMain.h"
#include "ofApp.h"
#include "Powerup.h"

Powerup::Powerup() {
	location.x = 0;
	location.y = 0;
	z = 0;
	w = 0;
	h = 0;
}

Powerup::Powerup(ofVec2f location, ofVec2f velocity, int z, int w, int h) {
	this->location.x = location.x;
	this->location.y = location.y;
	this->z = z;
	this->w = w;	
	this->h = h;
}

void Powerup::draw(ofImage powerupImage) {
	powerupImage.draw(this->location.x, this->location.y, this->z, this->w, this->h);
}

void Powerup::move() {
	++this->location.y;
	this->velocity.x = 50 * sin(location.x / 30);
}

bool Powerup::hitsPaddle(int paddleX, int level) {
	return (this->location.x >= paddleX - (250 / level) && this->location.x <= paddleX + (250 / level) && this->location.y >= ofGetHeight() - 125 && this->location.y <= ofGetHeight() - 100);
}

bool Powerup::offScreen() {
	return this->location.y >= ofGetHeight() + this->h;
}