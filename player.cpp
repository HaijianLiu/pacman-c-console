
/*==============================================================================
player.cpp　プレイヤープログラム
Author　　　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/

/*==============================================================================
インクルードファイル
==============================================================================*/
#include <stdio.h>
#include <wchar.h>
#include "player.h"
#include "console.h"
#include "controller.h"

/*==============================================================================
構造体の初期化
戻り値　構造体　Player
==============================================================================*/
Player initPlayer() {
	Player player;
	player.x            = 10 + SCREEN_LEFT; // X座標
	player.y            = 18;               // Y座標
	player.move         = 0;                // 移動方向
	player.color        = YELLOW;           // 色
	player.counter      = 0;                // パターン変わる計数
	player.super        = false;            // 無敵状態
	player.superCounter = 0;                // 無敵計数
	player.alive        = true;             // 生きているかどうか
	player.maker[0]     = L'●';             // パターン１
	player.maker[1]     = L'○';             // バターン２
	coordPrint(player.y,player.x,player.maker[player.counter],player.color);
	return player;
}

/*==============================================================================
プレイヤーの移動
==============================================================================*/
void movePlayer(Player* player, wchar_t* level, GameStatus* gameStatus) {
	// コントローラの取得
	player->move = getController(player->move);
	// もしプレイヤーが移動
	if (player->move != 0) {
		// 元位置の保存
		int x = player->x;
		int y = player->y;
		// 方向判断
		switch (player->move) {
			case KEY_UP:
				player->y -= 1;
				break;
			case KEY_DOWN:
				player->y += 1;
				break;
			case KEY_LEFT:
				player->x -= 1;
				// もし行き先が出口
				if (player->x <= SCREEN_LEFT) {
					player->x = SCREEN_LEFT + MAP_SIZE_X - 2;
				}
				break;
			case KEY_RIGHT:
				player->x += 1;
				// もし行き先が出口
				if (player->x >= SCREEN_LEFT + MAP_SIZE_X - 1) {
					player->x = SCREEN_LEFT+1;
				}
				break;
		}

		// もし行き先が空白
		if (*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) == L'　') {
			// プレイヤー移動
			coordPrint(y,x,L'　',0);
			player->counter = player->counter % 2;
			coordPrint(player->y,player->x,player->maker[player->counter],player->color);
			player->counter ++;
		}
		// もし行き先がアイテム
		else if (*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) == L'・') {
			// プレイヤー移動
			coordPrint(y,x,L'　',0);
			player->counter = player->counter % 2;
			coordPrint(player->y,player->x,player->maker[player->counter],player->color);
			player->counter ++;
			// マップデーターの更新
			*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) = L'　';
			// スーコアとゲームパラメータの更新
			gameStatus->score += SCORE_DOT_S;
			gameStatus->dots ++;
			updateScore(gameStatus);
		}
		// もし行き先が無敵
		else if (*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) == L'◎') {
			// プレイヤー移動
			coordPrint(y,x,L'　',0);
			player->counter = player->counter % 2;
			coordPrint(player->y,player->x,player->maker[player->counter],player->color);
			player->counter ++;
			// マップデーターの更新
			*(level + player->y*MAP_SIZE_X + player->x - SCREEN_LEFT) = L'　';
			// スーコアとゲームパラメータの更新
			gameStatus->score += SCORE_DOT_B;
			gameStatus->dots ++;
			player->super = true;
			player->superCounter = gameStatus->superTime;
			updateScore(gameStatus);
		}
		// もし行き先が壁、プレイヤーが止める
		else {
			player->x = x;
			player->y = y;
			player->move = 0;
		}
	}
}

/*==============================================================================
プレイヤーの更新
==============================================================================*/
void updatePlayer(Player* player, wchar_t* level, GameStatus* gameStatus) {
	// プレイヤーの更新率
	if (gameStatus->speedCounter % gameStatus->playerSpeed == 0) {
		// プレイヤー移動
		movePlayer(player,level,gameStatus);
		// もしプレイヤーが無敵
		if (player->superCounter > 0) {
			player->superCounter --;
			if (player->superCounter == 0) {
				player->super = false;
			}
		}
	}
}
