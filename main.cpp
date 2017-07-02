
#include <stdio.h>
#include <windows.h>
#include <wchar.h>

#include "main.h"

int main(void) {

	initConsole();

	GameStatus gameStatus = initGameStatus();

	wchar_t level[MAP_SIZE_X * MAP_SIZE_Y] = {};
	initLevel(level,&gameStatus);

	Player player = initPlayer();
	// ENEMY enemy[4] = initEnemy();

	while (1) {
		updatePlayer(&player,level,&gameStatus);
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
