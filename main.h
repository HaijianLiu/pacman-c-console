
/*==============================================================================
main.h　メインヘッダー
Author　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/

#ifndef _MAIN_H_
#define _MAIN_H_

/*==============================================================================
インクルードファイル
==============================================================================*/
#include "console.h"
#include "title.h"
#include "level.h"
#include "player.h"
#include "enemy.h"

/*==============================================================================
プロトタイプ宣言
==============================================================================*/
void updateMainTitle(GameStatus* gameStatus);
void updateMainGame(GameStatus* gameStatus);
void frameRateControl(GameStatus* gameStatus);
void updateGameOver(GameStatus* gameStatus);
void updateGameClear(wchar_t* level, GameStatus* gameStatus);

#endif
