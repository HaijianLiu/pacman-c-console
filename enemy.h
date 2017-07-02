
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "level.h"

typedef struct {
	int id, x, y, move, color;
	bool alive;
	wchar_t maker;
} Enemy;

Enemy initEnemy(int id);

// void movePlayer(Player* player, wchar_t* level, GameStatus* gameStatus);
//
// void updatePlayer(Player* player, wchar_t* level, GameStatus* gameStatus);

#endif
