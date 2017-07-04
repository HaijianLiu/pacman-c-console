
/*==============================================================================
title.cpp　タイトルプログラム
Author　　　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/

/*==============================================================================
インクルードファイル
==============================================================================*/
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include "title.h"
#include "console.h"
#include "controller.h"

/*==============================================================================
チュートリアルの表示
==============================================================================*/
void drawTutorial() {
	coordPrint(11,12,L"方向：←↑↓→　決定：ＥＮＴＥＲ",WHITE);
	getchar();
}

/*==============================================================================
タイトルデータの初期化
データの保存　wchar_t* titleText
==============================================================================*/
void initTitle(wchar_t* titleText) {
	system("cls");
	// wchar_t text[TITLE_SIZE_Y][TITLE_SIZE_X] = {
	// 	L"┏━━━━┓　┏━━━━━┓┏━━━━━┓┏━━━━┓",
	// 	L"┃・・・・┗┓┃・・・・・┃┃・・・・・┃┃・・・・┃",
	// 	L"┃・┏━┓・┃┃・┏━┓・┃┗━┓・┏━┛┃・┏━━┛",
	// 	L"┃・┃　┃・┃┃・┃　┃・┃　　┃・┃　　┃・┗━━┓",
	// 	L"┃・┃　┃・┃┃・┃　┃・┃　　┃・┃　　┃・・・・┃",
	// 	L"┃・┃　┃・┃┃・┃　┃・┃　　┃・┃　　┗━━┓・┃",
	// 	L"┃・┗━┛・┃┃・┗━┛・┃　　┃・┃　　┏━━┛・┃",
	// 	L"┃・・・・┏┛┃・・・・・┃　　┃・┃　　┃・・・・┃",
	// 	L"┗━━━━┛　┗━━━━━┛　　┗━┛　　┗━━━━┛",
	// };

	// タイトルデーター
	wchar_t text[TITLE_SIZE_Y][TITLE_SIZE_X] = {
		L"┏━━━━━┓┏━━━━━┓┏━━━━━┓┏━━━━┓",
		L"┃・・・・・┃┃・・・・・┃┃・・・・・┃┃・・・・┃",
		L"┃・┏━┓・┃┃・┏━┓・┃┃・┏━━━┛┃・┏━━┛",
		L"┃・┃　┃・┃┃・┃　┃・┃┃・┃　　　　┃・┗━━┓",
		L"┃・┗━┛・┃┃・┗━┛・┃┃・┃　　　　┃・・・・┃",
		L"┃・・・・・┃┃・・・・・┃┃・┃　　　　┗━━┓・┃",
		L"┃・┏━━━┛┃・┏━┓・┃┃・┗━━━┓┏━━┛・┃",
		L"┃・┃　　　　┃・┃　┃・┃┃・・・・・┃┃・・・・┃",
		L"┗━┛　　　　┗━┛　┗━┛┗━━━━━┛┗━━━━┛",
	};

	// データーの保存と表示
	for (int i = 0; i < TITLE_SIZE_Y; i++) {
		wcsncpy_s(&titleText[i*TITLE_SIZE_X],TITLE_SIZE_X,&text[i][0],TITLE_SIZE_X);
		if (i%2 == 0) {
			coordPrint(i+TITLE_COORD_Y,TITLE_COORD_X,&titleText[i * TITLE_SIZE_X],BLUE);
		} else {
			coordPrint(i+TITLE_COORD_Y,TITLE_COORD_X,&titleText[i * TITLE_SIZE_X],1);
		}
	}

	for (int i = 0; i < TITLE_SIZE_Y; i++) {
		for (int j = 0; j < TITLE_SIZE_X-1; j++) {
			if (*(titleText + i*TITLE_SIZE_X + j) == L'・') {
				coordPrint(i+TITLE_COORD_Y,j+TITLE_COORD_X,L'・',YELLOW);
			}
		}
	}
}

/*==============================================================================
タイトルの動画と操作
==============================================================================*/
void updateTitle(wchar_t* titleText, GameStatus* gameStatus) {

	// ローカル変数
	int count  = 0;
	bool press = false;
	int select = 1;
	int key    = 0;

	// もしゲームがスタートしない
	while (!press) {
		// タイトル動画
		if (count%5 == 0) {
			for (int i = 0; i < TITLE_SIZE_Y; i++) {
				if ((i+count)%2 == 0) {
					coordPrint(i+TITLE_COORD_Y,TITLE_COORD_X,&titleText[i * TITLE_SIZE_X],BLUE);
				} else {
					coordPrint(i+TITLE_COORD_Y,TITLE_COORD_X,&titleText[i * TITLE_SIZE_X],1);
				}
			}

			for (int i = 0; i < TITLE_SIZE_Y; i++) {
				for (int j = 0; j < TITLE_SIZE_X-1; j++) {
					if (*(titleText + i*TITLE_SIZE_X + j) == L'・') {
						coordPrint(i+TITLE_COORD_Y,j+TITLE_COORD_X,L'・',YELLOW);
					}
				}
			}
		}

		// キーの入力
		key = getController(0);
		if (key != 0) {
			switch (key) {
				case KEY_LEFT:
					if (select > 0) {
						select--;
					}
					break;
				case KEY_RIGHT:
					if (select < 2) {
						select++;
					}
					break;
				case KEY_ENTER:
					press = true;
					break;
			}
		}

		// 選択の更新
		switch (select) {
			case 0:
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X,L"ＥＡＳＹ",YELLOW);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+7,L"ＮＯＲＭＡＬ",GRAY);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+16,L"ＨＡＲＤ",GRAY);
				break;
			case 1:
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X,L"ＥＡＳＹ",GRAY);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+7,L"ＮＯＲＭＡＬ",YELLOW);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+16,L"ＨＡＲＤ",GRAY);
				break;
			case 2:
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X,L"ＥＡＳＹ",GRAY);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+7,L"ＮＯＲＭＡＬ",GRAY);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+16,L"ＨＡＲＤ",YELLOW);
				break;
		}

		count ++;
		Sleep(100);
	}

	// ゲームの難易度を更新
	gameStatus->hardness = select;
	switch (gameStatus->hardness) {
		case 0:
			gameStatus->enemySpeed = 10;
			gameStatus->superTime = 30;
			break;
		case 1:
			gameStatus->enemySpeed = 8;
			gameStatus->superTime = 20;
			break;
		case 2:
			gameStatus->enemySpeed = 6;
			gameStatus->superTime = 10;
			break;
	}
}
