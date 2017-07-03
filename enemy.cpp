
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

int getAI(Player* player, Enemy* enemy, wchar_t* pathMap, GameStatus* gameStatus) {

	int counter = 4;
	int m = enemy->move;

	while (1) {

		enemy->move = rand()%4 + 1;

		switch (enemy->move) {
			case UP:
				if (*(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' || *(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'　') {
					if (enemy->id > gameStatus->hardness) {
						if ( m != DOWN) {
							return UP;
						}
					}
					else {
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' && m != DOWN) {
							return UP;
						}
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■') {
							if (counter > 0) {
								if (player->y < enemy->y) {
									return UP;
								}
							} else {
								if (player->y <= enemy->y) {
									return UP;
								}
							}
						}
					}
				}
				break;
			case DOWN:
				if (*(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' || *(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'　') {
					if (enemy->id > gameStatus->hardness) {
						if (m != UP) {
							return DOWN;
						}
					}
					else {
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' && m != UP) {
							return DOWN;
						}
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■') {
							if (counter > 0) {
								if (player->y > enemy->y) {
									return DOWN;
								}
							} else {
								if (player->y >= enemy->y) {
									return DOWN;
								}
							}
						}
					}
				}
				break;
			case LEFT:
				if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'□' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'　') {
					if (enemy->id > gameStatus->hardness) {
						if (m != RIGHT) {
							return LEFT;
						}
					}
					else {
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' && m != RIGHT) {
							return LEFT;
						}
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■') {
							if (counter > 0) {
								if (player->x < enemy->x) {
									return LEFT;
								}
							} else {
								if (player->x <= enemy->x) {
									return LEFT;
								}
							}
						}
					}
				}
				break;
			case RIGHT:
				if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'□' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'　') {
					if (enemy->id > gameStatus->hardness) {
						if (m != LEFT) {
							return RIGHT;
						}
					}
					else {
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' && m != LEFT) {
							return RIGHT;
						}
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■') {
							if (counter > 0) {
								if (player->x > enemy->x) {
									return RIGHT;
								}
							} else {
								if (player->x >= enemy->x) {
									return RIGHT;
								}
							}
						}
					}
				}
				break;
		}
		counter --;
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
	// initEnemy
	for (int i = 0; i < ENEMY_GROUP-1; i++) {
		if (gameStatus->dots == gameStatus->enemyDelay*(i+1) && enemy->id == i+1) {
			coordPrint(enemy->y,enemy->x,L"　",enemy->color);
			enemy->x = 10 + SCREEN_LEFT;
			enemy->y = 10;
		}
	}
	// if Ai
	if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□') {
		enemy->move = getAI(player,enemy,pathMap,gameStatus);
	}
	// move enemy according behivaor
	moveEnemy(enemy,level);
}
