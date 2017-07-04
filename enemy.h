
/*==============================================================================
enemy.h　エネミーヘッダー
Author　　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/

#ifndef _ENEMY_H_
#define _ENEMY_H_

/*==============================================================================
インクルードファイル
==============================================================================*/
#include "level.h"
#include "player.h"

/*==============================================================================
構造体定義
==============================================================================*/
typedef struct {
	int id, x, y, move, color;
	wchar_t maker;
} Enemy;

/*==============================================================================
プロトタイプ宣言
==============================================================================*/
Enemy initEnemy(int id);
int getAI(Player* player, Enemy* enemy, wchar_t* pathMap, GameStatus* gameStatus);
void moveEnemy(Player* player, Enemy* enemy, wchar_t* level);
void updateEnemy(Player* player, Enemy* enemy, wchar_t* level, wchar_t* pathMap, GameStatus* gameStatus);

#endif
