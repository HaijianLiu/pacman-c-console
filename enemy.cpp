
/*==============================================================================
enemy.cpp　エネミープログラム
Author　　　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/

/*==============================================================================
インクルードファイル
==============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "enemy.h"
#include "console.h"

/*==============================================================================
マクロ定義
==============================================================================*/
// エネミーの移動方向
#define UP    (1)
#define DOWN  (2)
#define LEFT  (3)
#define RIGHT (4)

/*==============================================================================
構造体の初期化
==============================================================================*/
Enemy initEnemy(int id) {
	Enemy enemy;
	enemy.id       = id;   // エネミーID
	enemy.move     = 0;    // エネミー移動方向変数
	enemy.maker    = L'▲'; // エネミーパターン

	// エネミー初期位置とカラーの初期化
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

	// エネミーの表示
	coordPrint(enemy.y,enemy.x,enemy.maker,enemy.color);
	return enemy;
}

/*==============================================================================
エネミーAIの計算
戻り値：移動方向
==============================================================================*/
int getAI(Player* player, Enemy* enemy, wchar_t* pathMap, GameStatus* gameStatus) {

	int counter = 4;     // AI計算回数
	int m = enemy->move; // エネミー位置の保存

	// もしプレイヤーが無敵、プレイヤーを避ける
	if (player->super == true) {
		// 結果出るまでループ
		while (1) {

			enemy->move = rand()%4 + 1; // ランダム方向の取得

			// 行き先のチェック
			switch (enemy->move) {
				case UP:
					// 行き先が壁ではない
					if (*(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' || *(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'　') {
						// AIが必要ない場合
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' && m != DOWN) {
							return UP;
						}
						// AIが必要な場合
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■') {
							if (counter > 0) {
								if (player->y > enemy->y) {
									return UP;
								}
							} else {
								if (player->y >= enemy->y) {
									return UP;
								}
							}
						}
					}
					break;
				case DOWN:
					// 行き先が壁ではない
					if (*(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' || *(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'　') {
						// AIが必要ない場合
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' && m != UP) {
							return DOWN;
						}
						// AIが必要な場合
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■') {
							if (counter > 0) {
								if (player->y < enemy->y) {
									return DOWN;
								}
							} else {
								if (player->y <= enemy->y) {
									return DOWN;
								}
							}
						}
					}
					break;
				case LEFT:
					// 行き先が壁ではない
					if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'□' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'　') {
						// AIが必要ない場合
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' && m != RIGHT) {
							return LEFT;
						}
						// AIが必要な場合
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■') {
							if (counter > 0) {
								if (player->x > enemy->x) {
									return LEFT;
								}
							} else {
								if (player->x >= enemy->x) {
									return LEFT;
								}
							}
						}
					}
					break;
				case RIGHT:
					// 行き先が壁ではない
					if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'□' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'　') {
						// AIが必要ない場合
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' && m != LEFT) {
							return RIGHT;
						}
						// AIが必要な場合
						if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■') {
							if (counter > 0) {
								if (player->x < enemy->x) {
									return RIGHT;
								}
							} else {
								if (player->x <= enemy->x) {
									return RIGHT;
								}
							}
						}
					}
					break;
			}
			counter --;
		}
	}
	// もしプレイヤーが無敵ではない、プレイヤーを探す
	else {
		// 結果出るまでループ
		while (1) {

			enemy->move = rand()%4 + 1; // ランダム方向の取得

			switch (enemy->move) {
				case UP:
					// 行き先が壁ではない
					if (*(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' || *(pathMap + (enemy->y-1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'　') {
						// ゲームの難易度によって、AIがあるエネミーのIDをチェック
						// AIがない場合
						if (enemy->id > gameStatus->hardness) {
							if ( m != DOWN) {
								return UP;
							}
						}
						// AIがある場合
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
					// 行き先が壁ではない
					if (*(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□' || *(pathMap + (enemy->y+1)*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'　') {
						// ゲームの難易度によって、AIがあるエネミーのIDをチェック
						// AIがない場合
						if (enemy->id > gameStatus->hardness) {
							if (m != UP) {
								return DOWN;
							}
						}
						// AIがある場合
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
					// 行き先が壁ではない
					if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'□' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x - 1 - SCREEN_LEFT) == L'　') {
						// ゲームの難易度によって、AIがあるエネミーのIDをチェック
						// AIがない場合
						if (enemy->id > gameStatus->hardness) {
							if (m != RIGHT) {
								return LEFT;
							}
						}
						// AIがある場合
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
					// 行き先が壁ではない
					if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'□' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x + 1 - SCREEN_LEFT) == L'　') {
						// ゲームの難易度によって、AIがあるエネミーのIDをチェック
						// AIがない場合
						if (enemy->id > gameStatus->hardness) {
							if (m != LEFT) {
								return RIGHT;
							}
						}
						// AIがある場合
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
			// AI計算回数の減少
			counter --;
		}
	}
}

/*==============================================================================
エネミーの移動
==============================================================================*/
void moveEnemy(Player* player, Enemy* enemy, wchar_t* level) {

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

		// もしプレイヤーが無敵、色が変わる
		if (player->super == true) {
			coordPrint(enemy->y,enemy->x,enemy->maker,BLUE);
		}
		else {
			coordPrint(enemy->y,enemy->x,enemy->maker,enemy->color);
		}
	}
}

/*==============================================================================
エネミーの更新
==============================================================================*/
void updateEnemy(Player* player, Enemy* enemy, wchar_t* level, wchar_t* pathMap, GameStatus* gameStatus) {

	// プレイヤー更新率のチェック
	if (gameStatus->speedCounter % gameStatus->playerSpeed == 0) {

		// 新しいエネミーの初期化
		for (int i = 0; i < ENEMY_GROUP-1; i++) {
			if (gameStatus->dots == gameStatus->enemyDelay*(i+1) && enemy->id == i+1) {
				coordPrint(enemy->y,enemy->x,L"　",enemy->color);
				enemy->x = 10 + SCREEN_LEFT;
				enemy->y = 10;
			}
		}

		// もしプレイヤーとエネミーが同じい位置にいる
		if ( (enemy->x == player->x) && (enemy->y == player->y) ) {
			// もしプレイヤーが無敵ではない、プレイヤーが死ぬ
			if (player->super == false) {
				player->alive = false;
			}
			// もしプレイヤーが無敵、エネミーがリセット
			else {
				enemy->x = 10 + SCREEN_LEFT;
				enemy->y = 10;
				gameStatus->score += SCORE_ENEMY;
			}
		}
	}

	// エネミー更新率のチェック
	if (gameStatus->speedCounter % gameStatus->enemySpeed == 0) {

		// もしAIが必要かもしれない時、AIが実行
		if (*(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'■' || *(pathMap + enemy->y*MAP_SIZE_X + enemy->x - SCREEN_LEFT) == L'□') {
			enemy->move = getAI(player,enemy,pathMap,gameStatus);
		}
		// もしAIが必要ない場合、エネミーが普通に移動
		moveEnemy(player,enemy,level);

		// もしプレイヤーとエネミーが同じい位置にいる
		if ( (enemy->x == player->x) && (enemy->y == player->y) ) {
			// もしプレイヤーが無敵ではない、プレイヤーが死ぬ
			if (player->super == false) {
				player->alive = false;
			}
			// もしプレイヤーが無敵、エネミーがリセット
			else {
				enemy->x = 10 + SCREEN_LEFT;
				enemy->y = 10;
				gameStatus->score += SCORE_ENEMY;
			}
		}
	}
}
