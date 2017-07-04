
/*==============================================================================
main.cpp　メインプログラム
Author　　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/

/*==============================================================================
インクルードファイル
==============================================================================*/
#include <stdio.h>
#include <windows.h>
#include "main.h"

/*==============================================================================
 main関数
==============================================================================*/
int main(void) {

	// コンソールの初期化
	initConsole();
	// チュートリアルの表示
	drawTutorial();

	// メインゲームループ（ゲームオーバーしたら、タイトルに戻る）
	while (true) {
		// ゲームパラメータの初期化
		GameStatus gameStatus = initGameStatus();
		// タイトルの更新
		updateMainTitle(&gameStatus);
		// メインゲームの更新
		updateMainGame(&gameStatus);
	}

	// 終了
	return 0;
}


/*==============================================================================
タイトルの更新
==============================================================================*/
void updateMainTitle(GameStatus* gameStatus) {
	wchar_t titleText[TITLE_SIZE_X * TITLE_SIZE_Y] = {};
	initTitle(titleText);
	updateTitle(titleText,gameStatus);
}

/*==============================================================================
メインゲームの更新
==============================================================================*/
void updateMainGame(GameStatus* gameStatus) {

	// ライフが残ったら、ループ
	while (gameStatus->life >= 0) {

		// ステイージの表示
		drawStage(gameStatus);
		// マップの初期化
		wchar_t level[MAP_SIZE_X * MAP_SIZE_Y] = {};
		initLevel(level,gameStatus);
		// AIマップの初期化
		wchar_t pathMap[MAP_SIZE_X * MAP_SIZE_Y] = {};
		initPathMap(pathMap);
		// プレイヤーの初期化
		Player player = initPlayer();
		// エネミーグループの初期化
		Enemy enemy[ENEMY_GROUP];
		for (int i = 0; i < ENEMY_GROUP; i++) {
			 enemy[i] = initEnemy(i);
		}

		// もしプレイヤーが生きている、かつ、ゲームがクリアしていない、ループ…
		while (player.alive && gameStatus->dots < DOTS_MAX) {
			// プレイヤーの更新
			updatePlayer(&player,level,gameStatus);
			// エネミーの更新
			for (int i = 0; i < ENEMY_GROUP; i++) {
				updateEnemy(&player,enemy+i,level,pathMap,gameStatus);
			}
			// フレイム率の調整
			frameRateControl(gameStatus);
		}

		// もしプレイヤーが死んでいる
		if (player.alive == false) {
			// ゲームパラメータの更新
			updateGameOver(gameStatus);
		}
		// もしゲームクリア
		if (gameStatus->dots == DOTS_MAX) {
			// ゲームパラメータの更新
			updateGameClear(level,gameStatus);
		}
	}
}

/*==============================================================================
フレイム率の調整
==============================================================================*/
void frameRateControl(GameStatus* gameStatus) {
	// 待ち
	Sleep(gameStatus->sleepTime);
	// 速度調整変数のリセット
	if (gameStatus->speedCounter % (gameStatus->playerSpeed * gameStatus->enemySpeed) == 0 ) {
		gameStatus->speedCounter = 0;
	}
	// 速度計数 ++
	gameStatus->speedCounter ++;
}

/*==============================================================================
ゲームオーバーパラメータの更新
==============================================================================*/
void updateGameOver(GameStatus* gameStatus) {
	// 最大スーコアの更新
	gameStatus->life --;
	if (gameStatus->score > gameStatus->hiScore) {
		gameStatus->hiScore = gameStatus->score;
	}
	gameStatus->score = 0;
	gameStatus->dots = 0;
	// 表示
	drawGameOver();
	Sleep(2000);
}

/*==============================================================================
ゲームクリアパラメータの更新
==============================================================================*/
void updateGameClear(wchar_t* level, GameStatus* gameStatus) {
	// ステージ数の更新
	gameStatus->stage ++;
	gameStatus->dots = 0;
	// 表示
	animeGameClear(level);
}
