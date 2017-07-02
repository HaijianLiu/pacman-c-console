
#include <stdio.h>
#include <windows.h>

#include "main.h"

int main(void) {

	// Set console status
	initConsole();

	// Init GameStatus
	GameStatus gameStatus = initGameStatus();

	// Init Map
	wchar_t level[MAP_SIZE_X * MAP_SIZE_Y] = {};
	initLevel(level,&gameStatus);
	// Init Path Map
	wchar_t pathMap[MAP_SIZE_X * MAP_SIZE_Y] = {};
	initPathMap(pathMap);

	// Init Player
	Player player = initPlayer();


	// Enemy enemy = initEnemy(0);
	// Init Enemy Group
	Enemy enemy[ENEMY_GROUP];
	for (int i = 0; i < ENEMY_GROUP; i++) {
		 enemy[i] = initEnemy(i);
	}

	while (1) {
		updatePlayer(&player,level,&gameStatus);
		updateEnemy(&player,enemy,level,pathMap,&gameStatus);
		Sleep(NORMAL);
	}

	// do {
	// 	updatePlayer(player,enemy,level,gameStatus);
	// 	updateEnemy(player,enemy,level,gameStatus);
	// 	updateGameStatus(gameStatus);
	//
	// } while(gameStatus->gameOver == false);

	getchar();
	return 0;
}
