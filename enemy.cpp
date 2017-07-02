
#include <stdio.h>
#include <wchar.h>

#include "enemy.h"
#include "console.h"

Enemy initEnemy(int id) {
	Enemy enemy;
	enemy.id       = id;
	enemy.move     = 0;
	enemy.alive    = true;
	enemy.maker    = L'▲';

	switch (id) {
		case 0:
			enemy.x        = 10 + SCREEN_LEFT;
			enemy.y        = 10;
			enemy.color    = RED;
			break;
		case 1:
			enemy.x        = 9 + SCREEN_LEFT;
			enemy.y        = 12;
			enemy.color    = CYAN;
			break;
		case 2:
			enemy.x        = 10 + SCREEN_LEFT;
			enemy.y        = 12;
			enemy.color    = PINK;
			break;
		case 3:
			enemy.x        = 11 + SCREEN_LEFT;
			enemy.y        = 12;
			enemy.color    = GREEN;
			break;
	}

	coordPrint(enemy.y,enemy.x,enemy.maker,enemy.color);
	return enemy;
}

// void movePlayer(Player* player, wchar_t* level, GameStatus* gameStatus) {
// 	player->move = getController(player->move);
// 	if (player->move != 0) {
// 		int x = player->x;
// 		int y = player->y;
// 		switch (player->move) {
// 			case KEY_UP:
// 				player->y -= 1;
// 				break;
// 			case KEY_DOWN:
// 				player->y += 1;
// 				break;
// 			case KEY_LEFT:
// 				player->x -= 1;
// 				break;
// 			case KEY_RIGHT:
// 				player->x += 1;
// 				break;
// 		}
//
// 		if (*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) == L'　') {
// 			coordPrint(y,x,L'　',0);
// 			player->counter = player->counter % 2;
// 			coordPrint(player->y,player->x,player->maker[player->counter],player->color);
// 			player->counter ++;
// 		} else
//
// 		if (*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) == L'・') {
// 			coordPrint(y,x,L'　',0);
// 			player->counter = player->counter % 2;
// 			coordPrint(player->y,player->x,player->maker[player->counter],player->color);
// 			player->counter ++;
// 			// Update map
// 			*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) = L'　';
// 			// Update status
// 			gameStatus->score += SCORE_DOT_S;
// 			updateScore(gameStatus);
// 		} else
//
// 		if (*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) == L'◎') {
// 			coordPrint(y,x,L'　',0);
// 			player->counter = player->counter % 2;
// 			coordPrint(player->y,player->x,player->maker[player->counter],player->color);
// 			player->counter ++;
// 			// Update map
// 			*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) = L'　';
// 			// Update status
// 			gameStatus->score += SCORE_DOT_B;
// 			updateScore(gameStatus);
// 		} else
//
// 		{
// 			player->x = x;
// 			player->y = y;
// 		}
// 	}
// }
//
// void updatePlayer(Player* player, wchar_t* level, GameStatus* gameStatus) {
// 	movePlayer(player,level,gameStatus);
// }
