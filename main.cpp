
#include <stdio.h>
#include <windows.h>

#include "main.h"



int main(void) {

	// Set console status
	initConsole();

	// Init GameStatus
	GameStatus gameStatus = initGameStatus();

	drawTutorial();
	// Main Title Screen
	updateMainTitle(&gameStatus);
	// Main Game
	updateMainGame(&gameStatus);

	return 0;
}



void updateMainTitle(GameStatus* gameStatus) {
	wchar_t titleText[TITLE_SIZE_X * TITLE_SIZE_Y] = {};
	initTitle(titleText);
	updateTitle(titleText,gameStatus);
}

void updateMainGame(GameStatus* gameStatus) {

	while (gameStatus->life >= 0) {

		drawStage(gameStatus);
		// Init Map
		wchar_t level[MAP_SIZE_X * MAP_SIZE_Y] = {};
		initLevel(level,gameStatus);
		// Init Path Map
		wchar_t pathMap[MAP_SIZE_X * MAP_SIZE_Y] = {};
		initPathMap(pathMap);
		// Init Player
		Player player = initPlayer();
		// Init Enemy Group
		Enemy enemy[ENEMY_GROUP];
		for (int i = 0; i < ENEMY_GROUP; i++) {
			 enemy[i] = initEnemy(i);
		}

		while (player.alive && gameStatus->dots < DOTS_MAX) {
			updatePlayer(&player,level,gameStatus);
			for (int i = 0; i < ENEMY_GROUP; i++) {
				updateEnemy(&player,enemy+i,level,pathMap,gameStatus);
			}
			// speed control
			Sleep(gameStatus->sleepTime);
			// reset speedCounter
			if (gameStatus->speedCounter % (gameStatus->playerSpeed * gameStatus->enemySpeed) == 0 ) {
				gameStatus->speedCounter = 0;
			}
			gameStatus->speedCounter ++;
		}
		if (player.alive == false) {
			gameStatus->life --;
			if (gameStatus->score > gameStatus->hiScore) {
				gameStatus->hiScore = gameStatus->score;
			}
			gameStatus->score = 0;
			gameStatus->dots = 0;

			drawGameOver();
			Sleep(2000);
		}
		if (gameStatus->dots == DOTS_MAX) {
			gameStatus->stage ++;
			gameStatus->dots = 0;
			animeGameClear(level);
		}
	}
}
