#pragma once

#include "ofMain.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Powerup.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		const int START_SCREEN = 0;
		const int GAME_SCREEN = 1;
		const int GAME_OVER_SCREEN = 2;
		const int WIN_SCREEN = 3;

		int gameState = START_SCREEN;

		int livesLeft = 4;
		int score = 0;
		int level = 0;
		int allDestroyed = 0;
		bool allBlocksCleared = false;

		Paddle* mainPaddle;
		Ball* mainBall;
		Ball* bonusBall;
		Powerup* mainPowerup;
		vector<Block*> blocks;
		string row;
		ofSoundPlayer bumperSound;
		ofSoundPlayer blockSoundR;
		ofSoundPlayer blockSoundG;
		ofSoundPlayer blockSoundB;
		ofSoundPlayer playerWinSound;
		ofSoundPlayer gameOverSound;
		ofTrueTypeFont font1;
		ofTrueTypeFont font2;
		ofTrueTypeFont font3;
		ofImage powerupImage;

		void drawStartScreen();
		void drawGameScreen();
		void drawGameOverScreen();
		void drawWinScreen();
		void drawLives();
		void loadFont();
		void loadSound();
		void prepareLevel(int level);
		void destroyBrickLogic();
		void powerupLogic();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
