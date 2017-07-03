
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "level.h"

typedef struct {
	int x, y, move, color, counter, superCounter;
	bool super, alive;
	wchar_t maker[2];
} Player;

Player initPlayer();

void movePlayer(Player* player, wchar_t* level, GameStatus* gameStatus);

void updatePlayer(Player* player, wchar_t* level, GameStatus* gameStatus);

#endif
