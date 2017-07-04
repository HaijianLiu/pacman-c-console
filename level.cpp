
/*==============================================================================
level.cpp　マッププログラム
Author　　　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/

/*==============================================================================
インクルードファイル
==============================================================================*/
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include "level.h"
#include "console.h"

/*==============================================================================
構造体の初期化
戻り値：　構造体
==============================================================================*/
GameStatus initGameStatus() {
	GameStatus gameStatus;
	gameStatus.score        = 0;  // プレイヤースーコア
	gameStatus.hiScore      = 0;  // 最高スーコア
	gameStatus.dots         = 0;  // ゲットしたドット
	gameStatus.hardness     = 0;  // ゲームの難易度（賢い敵の数値-1）
	gameStatus.enemyDelay   = 10; // エネミー初期化の間隔
	gameStatus.sleepTime    = 30; // メインゲームの更新率
	gameStatus.playerSpeed  = 6;  // プレイヤーの更新率
	gameStatus.enemySpeed   = 10; // エネミーの更新率
	gameStatus.speedCounter = 0;  // ゲーム更新率とプレイヤー更新率とエネミー更新率を管理記数
	gameStatus.life         = 2;  // 残りプレイヤー
	gameStatus.stage        = 1;  // ステージ数
	gameStatus.superTime    = 50; // 無敵時間
	return gameStatus;
}

/*==============================================================================
アイテムの初期化
==============================================================================*/
void initItem(wchar_t* level) {
	// マップをチェックして、アイテムの色をイエローにする
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		for (int j = 0; j < MAP_SIZE_X-1; j++) {
			if (*(level + i*MAP_SIZE_X + j) == L'・') {
				coordPrint(i,j+SCREEN_LEFT,L'・',YELLOW);
			}
			if (*(level + i*MAP_SIZE_X + j) == L'◎') {
				coordPrint(i,j+SCREEN_LEFT,L'◎',YELLOW);
			}
		}
	}
}

/*==============================================================================
マップの初期化と表示
ゲームUIの表示
マップデータの取得　wchar_t* level　に保存
==============================================================================*/
void initLevel(wchar_t* level, GameStatus* gameStatus) {

	// ゲームマップ
	wchar_t map[MAP_SIZE_Y][MAP_SIZE_X] = {
		L"┏━━━━━━━━━┳━━━━━━━━━┓",
		L"┃◎・・・・・・・・┃・・・・・・・・◎┃",
		L"┃・┏━┓・┏━┓・┃・┏━┓・┏━┓・┃",
		L"┃・┃　┃・┃　┃・┃・┃　┃・┃　┃・┃",
		L"┃・┗━┛・┗━┛・┃・┗━┛・┗━┛・┃",
		L"┃・・・・・・・・・・・・・・・・・・・┃",
		L"┃・┏━┓・┃・┏━━━┓・┃・┏━┓・┃",
		L"┃・┗━┛・┃・┗━┳━┛・┃・┗━┛・┃",
		L"┃・・・・・┃・・・┃・・・┃・・・・・┃",
		L"┗━━━┓・┣━━　┃　━━┫・┏━━━┛",
		L"　　　　┃・┃　　　　　　　┃・┃　　　　",
		L"━━━━┛・┃　┏━━━┓　┃・┗━━━━",
		L"　　　　　・　　┃　　　┃　　・　　　　　",
		L"━━━━┓・┃　┗━━━┛　┃・┏━━━━",
		L"　　　　┃・┃　　　　　　　┃・┃　　　　",
		L"┏━━━┛・┃　━━┳━━　┃・┗━━━┓",
		L"┃・・・・・・・・・┃・・・・・・・・・┃",
		L"┃・━━┓・━━━・┃・━━━・┏━━・┃",
		L"┃・・・┃・・・・・・・・・・・┃・・・┃",
		L"┣━┓・┃・┃・┏━━━┓・┃・┃・┏━┫",
		L"┣━┛・┃・┃・┗━┳━┛・┃・┃・┗━┫",
		L"┃・・・・・┃・・・┃・・・┃・・・・・┃",
		L"┃・━━━━┻━━・┃・━━┻━━━━・┃",
		L"┃◎・・・・・・・・・・・・・・・・・◎┃",
		L"┗━━━━━━━━━━━━━━━━━━━┛",
	};

	for (int i = 0; i < MAP_SIZE_Y; i++) {
		// マップデータの保存
		wcsncpy_s(&level[i*MAP_SIZE_X],MAP_SIZE_X,&map[i][0],MAP_SIZE_X);
		// マップの表示
		coordPrint(i,SCREEN_LEFT,&level[i * MAP_SIZE_X],BLUE);
	}

	// アイテムの初期化
	initItem(level);
	// エネミー扉の表示
	coordPrint(11,10 + SCREEN_LEFT,L"━",WHITE);

	// UIの表示
	// 最高スーコアの表示
	coordPrint(SCORE_COORD_Y,SCORE_COORD_X,L"HIGH SCORE",RED);
	// プレイヤースーコアの表示
	coordPrint(SCORE_COORD_Y+3,SCORE_COORD_X,L"1UP",RED);
	// スーコアの更新
	updateScore(gameStatus);
	// 残りプレイヤー数の表示
	for (int i = 0; i < gameStatus->life; i++) {
		coordPrint(SCORE_COORD_Y+21-i,SCORE_COORD_X+1,L'●',YELLOW);
	}
}

/*==============================================================================
AIマップの初期化
AIマップデータの取得　wchar_t* pathMap　に保存
==============================================================================*/
void initPathMap(wchar_t* pathMap) {

	// AIマップ
	// ■がAI判断位置、□がランダム判断位置
	wchar_t map[MAP_SIZE_Y][MAP_SIZE_X] = {
		L"┏━━━━━━━━━┳━━━━━━━━━┓",
		L"┃□　　　■　　　□┃□　　　■　　　□┃",
		L"┃　┏━┓　┏━┓　┃　┏━┓　┏━┓　┃",
		L"┃　┃　┃　┃　┃　┃　┃　┃　┃　┃　┃",
		L"┃　┗━┛　┗━┛　┃　┗━┛　┗━┛　┃",
		L"┃■　　　■　■　□　□　■　■　　　■┃",
		L"┃　┏━┓　┃　┏━━━┓　┃　┏━┓　┃",
		L"┃　┗━┛　┃　┗━┳━┛　┃　┗━┛　┃",
		L"┃□　　　■┃□　□┃□　□┃■　　　□┃",
		L"┗━━━┓　┣━━　┃　━━┫　┏━━━┛",
		L"　　　　┃　┃□　□□□　□┃　┃　　　　",
		L"━━━━┛　┃　┏━━━┓　┃　┗━━━━",
		L"　　　　　■　■┃　　　┃■　■　　　　　",
		L"━━━━┓　┃　┗━━━┛　┃　┏━━━━",
		L"　　　　┃　┃■　　　　　■┃　┃　　　　",
		L"┏━━━┛　┃　━━┳━━　┃　┗━━━┓",
		L"┃□　　　■　■　□┃□　■　■　　　□┃",
		L"┃　━━┓　━━━　┃　━━━　┏━━　┃",
		L"┃□　□┃■　■　□　□　■　■┃□　□┃",
		L"┣━┓　┃　┃　┏━━━┓　┃　┃　┏━┫",
		L"┣━┛　┃　┃　┗━┳━┛　┃　┃　┗━┫",
		L"┃□　■　□┃□　□┃□　□┃□　■　□┃",
		L"┃　━━━━┻━━　┃　━━┻━━━━　┃",
		L"┃□　　　　　　　■　■　　　　　　　□┃",
		L"┗━━━━━━━━━━━━━━━━━━━┛",
	};

	// マップデータの保存
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		wcsncpy_s(&pathMap[i*MAP_SIZE_X],MAP_SIZE_X,&map[i][0],MAP_SIZE_X);
	}
}

/*==============================================================================
スーコアの更新
==============================================================================*/
void updateScore(GameStatus* gameStatus) {
	coordPrint(SCORE_COORD_Y+1,SCORE_COORD_X,gameStatus->hiScore,WHITE);
	coordPrint(SCORE_COORD_Y+4,SCORE_COORD_X,gameStatus->score,WHITE);
}

/*==============================================================================
ゲームオーバー文字の表示
==============================================================================*/
void drawGameOver() {
	coordPrint(12,13,L"ＧＡＭＥ　ＯＶＥＲ",WHITE);
}

/*==============================================================================
ステージ画面の表示
==============================================================================*/
void drawStage(GameStatus* gameStatus) {
	system("cls");
	coordPrint(11,13,L"ＳＴＡＧＥ",WHITE);
	coordPrint(11,20,gameStatus->stage,WHITE);
	coordPrint(11,23,L'●',YELLOW);
	coordPrint(11,25,L'Ｘ',WHITE);
	coordPrint(11,27,gameStatus->life,WHITE); // 残りプレイヤー数
	Sleep(2000);
}

/*==============================================================================
ゲームクリアのエフェクト
==============================================================================*/
void animeGameClear(wchar_t* level) {
	for (int j = 0; j < 6; j++) {
		if (j%2 == 0) {
			for (int i = 0; i < MAP_SIZE_Y; i++) {
				coordPrint(i,SCREEN_LEFT,&level[i * MAP_SIZE_X],WHITE);
			}
		}
		else {
			for (int i = 0; i < MAP_SIZE_Y; i++) {
				coordPrint(i,SCREEN_LEFT,&level[i * MAP_SIZE_X],BLUE);
			}
		}
		Sleep(500);
	}
}
