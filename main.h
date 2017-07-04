
#ifndef _MAIN_H_
#define _MAIN_H_

#include "console.h"
#include "title.h"
#include "level.h"
#include "player.h"
#include "enemy.h"

void updateMainTitle(GameStatus* gameStatus);
void updateMainGame(GameStatus* gameStatus);
void frameRateControl(GameStatus* gameStatus);
void updateGameOver(GameStatus* gameStatus);
void updateGameClear(wchar_t* level, GameStatus* gameStatus);

#endif
