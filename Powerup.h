#pragma once

class Powerup {
public:
	ofVec2f location;
	ofVec2f velocity;
	int z;
	int w;
	int h;
	Powerup();
	Powerup(ofVec2f location, ofVec2f velocity, int z, int w, int h);
	void draw(ofImage powerupImage);
	void move();
	bool hitsPaddle(int paddleX, int level);
	bool offScreen();
};
