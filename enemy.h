
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "level.h"
#include "player.h"

typedef struct {
	int id, x, y, move, color;
	bool alive;
	wchar_t maker;
} Enemy;

Enemy initEnemy(int id);

int getAI(Enemy* enemy, wchar_t* pathMap);

void moveEnemy(Enemy* enemy, wchar_t* level);

void updateEnemy(Player* player, Enemy* enemy, wchar_t* level, wchar_t* pathMap, GameStatus* gameStatus);

#endif
