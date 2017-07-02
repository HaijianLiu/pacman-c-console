
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "enemy.h"
#include "console.h"

#define UP (1)
#define DOWN (2)
#define LEFT (3)
#define RIGHT (4)


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

int getAI(Enemy* enemy, wchar_t* pathMap) {

	int m = enemy->move;

	while (1) {

		enemy->move = rand()%4 + 1;

		switch (enemy->move) {
			case UP:
				if (m != DOWN) {
					if (*(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'　') {
						return UP;
					}
				}
			case DOWN:
				if (m != UP) {
					if (*(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'　') {
						return DOWN;
					}
				}
			case LEFT:
				if (m != RIGHT) {
					if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'　') {
						return LEFT;
					}
				}
			case RIGHT:
				if (m != LEFT) {
					if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'　') {
						return RIGHT;
					}
				}
		}
	}
}

void moveEnemy(Enemy* enemy, wchar_t* level) {

	if (enemy->move != 0) {
		int x = enemy->x;
		int y = enemy->y;
		switch (enemy->move) {
			case UP:
				enemy->y -= 1;
				break;
			case DOWN:
				enemy->y += 1;
				break;
			case LEFT:
				enemy->x -= 1;
				if (enemy->x <= SCREEN_LEFT) {
					enemy->x = SCREEN_LEFT + MAP_SIZE_X - 2;
				}
				break;
			case RIGHT:
				enemy->x += 1;
				if (enemy->x >= SCREEN_LEFT + MAP_SIZE_X - 1) {
					enemy->x = SCREEN_LEFT+1;
				}
				break;
		}

		coordPrint(y,x,*(level + y*MAP_SIZE_X + x - SCREEN_LEFT),YELLOW);
		coordPrint(enemy->y,enemy->x,enemy->maker,enemy->color);
	}
}

void updateEnemy(Player* player, Enemy* enemy, wchar_t* level, wchar_t* pathMap, GameStatus* gameStatus) {
	if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■') {
		enemy->move = getAI(enemy,pathMap);
	}
	moveEnemy(enemy,level);
}
