﻿
#include <stdio.h>
#include <wchar.h>

#include "player.h"
#include "console.h"
#include "controller.h"

Player initPlayer() {
	Player player;
	player.x        = 10 + SCREEN_LEFT;
	player.y        = 18;
	player.move     = 0;
	player.color    = YELLOW;
	player.counter  = 0;
	player.super    = false;
	player.superCounter = 0;
	player.alive    = true;
	player.maker[0] = L'●';
	player.maker[1] = L'○';
	coordPrint(player.y,player.x,player.maker[player.counter],player.color);
	return player;
}

void movePlayer(Player* player, wchar_t* level, GameStatus* gameStatus) {
	player->move = getController(player->move);
	if (player->move != 0) {
		int x = player->x;
		int y = player->y;
		switch (player->move) {
			case KEY_UP:
				player->y -= 1;
				break;
			case KEY_DOWN:
				player->y += 1;
				break;
			case KEY_LEFT:
				player->x -= 1;
				if (player->x <= SCREEN_LEFT) {
					player->x = SCREEN_LEFT + MAP_SIZE_X - 2;
				}
				break;
			case KEY_RIGHT:
				player->x += 1;
				if (player->x >= SCREEN_LEFT + MAP_SIZE_X - 1) {
					player->x = SCREEN_LEFT+1;
				}
				break;
		}

		if (*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) == L'　') {
			coordPrint(y,x,L'　',0);
			player->counter = player->counter % 2;
			coordPrint(player->y,player->x,player->maker[player->counter],player->color);
			player->counter ++;
		} else

		if (*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) == L'・') {
			coordPrint(y,x,L'　',0);
			player->counter = player->counter % 2;
			coordPrint(player->y,player->x,player->maker[player->counter],player->color);
			player->counter ++;
			// Update map
			*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) = L'　';
			// Update status
			gameStatus->score += SCORE_DOT_S;
			gameStatus->dots ++;
			updateScore(gameStatus);
		} else

		if (*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) == L'◎') {
			coordPrint(y,x,L'　',0);
			player->counter = player->counter % 2;
			coordPrint(player->y,player->x,player->maker[player->counter],player->color);
			player->counter ++;
			// Update map
			*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) = L'　';
			// Update status
			gameStatus->score += SCORE_DOT_B;
			gameStatus->dots ++;
			player->super = true;
			player->superCounter = gameStatus->superTime;
			updateScore(gameStatus);
		} else

		{
			player->x = x;
			player->y = y;
			player->move = 0;
		}
	}
}

void updatePlayer(Player* player, wchar_t* level, GameStatus* gameStatus) {
	if (gameStatus->speedCounter % gameStatus->playerSpeed == 0) {
		movePlayer(player,level,gameStatus);
		if (player->superCounter > 0) {
			player->superCounter --;
		}
		else {
			player->super = false;
		}
	}
}
