#include "Ball.h"
#include "ofMain.h"

Ball::Ball() {
	location.x = 100;
	location.y = 100;
	size = 25;
	color = ofColor(255);
}

Ball::Ball(ofVec2f location, ofVec2f velocity, ofVec2f acceleration, float size, ofColor color) {
	this->location = location;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->size = size;
	this->color = color;
}

void Ball::draw() {
	ofSetColor(color);
	ofDrawCircle(location, 50);
}

void Ball::move() {
	location += velocity;
}

void Ball::applyForce(ofVec2f force) {
	acceleration += force;
	velocity += acceleration;
}

void Ball::bounce(int paddleX, int level, ofSoundPlayer bumperSound) {
	if (this->location.x <= this->size || this->location.x >= ofGetWidth() - this->size) {
		velocity.x *= -1;
		velocity.rotate(ofRandom(-5, 5));
	}
	if (this->location.y <= 25) {
		velocity.y *= -1;
		velocity.rotate(ofRandom(-5, 5));
	}
	if (this->location.x >= paddleX - (250 / level) && this->location.x <= paddleX + (250 / level) && this->location.y >= ofGetHeight() - 125 && this->location.y <= ofGetHeight() - 100) {
		velocity.y *= -1;
		velocity.rotate(ofRandom(-5, 5));
		bumperSound.play();
	}
}

void Ball::offScreen(int livesLeft) {
	if (this->location.y >= ofGetHeight() + this->size) {
		this->reset();
		livesLeft--;
	}
}

bool Ball::hits(int x, int y, string row) {
	return this->location.x <= x + ((ofGetWidth() / (row.size() * 2)) + this->size) && this->location.x >= x - ((ofGetWidth() / (row.size() * 2)) + this->size) && this->location.y <= y + 75 && this->location.y >= y - 75;
}

void Ball::reset() {
	this->location = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
}