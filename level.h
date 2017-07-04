
/*==============================================================================
level.h　マップヘッダー
Author　　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/

#ifndef _LEVEL_H_
#define _LEVEL_H_

/*==============================================================================
マクロ定義
==============================================================================*/
// 座標
#define MAP_SIZE_X    (22)                       // マップの大きさ
#define MAP_SIZE_Y    (25)                       // マップの大きさ
#define SCREEN_LEFT   (7)                        // マップの位置
#define SCORE_COORD_X (SCREEN_LEFT + MAP_SIZE_X) // スーコアの位置
#define SCORE_COORD_Y (1)                        // スーコアの位置
// スーコア
#define SCORE_DOT_S   (10)                       // ドットのスーコア
#define SCORE_DOT_B   (50)                       // 無敵のスーコア
#define SCORE_ENEMY   (200)                      // 敵のスーコア
// マップパラメータ
#define ENEMY_GROUP   (4)                        // 敵数
#define DOTS_MAX      (189)                      // マップ上のドット数

/*==============================================================================
構造体定義
==============================================================================*/
typedef struct {
	int score, hiScore, dots, hardness, enemyDelay, sleepTime, playerSpeed, enemySpeed, speedCounter, life, stage, superTime;
} GameStatus;

/*==============================================================================
プロトタイプ宣言
==============================================================================*/
GameStatus initGameStatus();
void initItem(wchar_t* level);
void initLevel(wchar_t* map, GameStatus* gameStatus);
void initPathMap(wchar_t* pathMap);
void updateScore(GameStatus* gameStatus);
void drawGameOver();
void drawStage(GameStatus* gameStatus);
void animeGameClear(wchar_t* level);

#endif
