
#include <stdio.h>
#include <windows.h>
#include <wchar.h>

#include "level.h"
#include "console.h"

GameStatus initGameStatus() {
	GameStatus gameStatus;
	gameStatus.score = 0;
	gameStatus.hiScore = 0;
	gameStatus.dots = 0;
	gameStatus.enemyDelay = 10;
	gameStatus.hardness = 0;
	gameStatus.sleepTime = 180;
	gameStatus.life = 2;
	gameStatus.stage = 1;
	gameStatus.superTime = 400;
	return gameStatus;
}

void initItem(wchar_t* level) {
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


void initLevel(wchar_t* level, GameStatus* gameStatus) {

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
		wcsncpy_s(&level[i*MAP_SIZE_X],MAP_SIZE_X,&map[i][0],MAP_SIZE_X);
		coordPrint(i,SCREEN_LEFT,&level[i * MAP_SIZE_X],BLUE);
	}

	initItem(level);
	coordPrint(11,10 + SCREEN_LEFT,L"━",WHITE);

	// "HIGH SCORE"
	coordPrint(SCORE_COORD_Y,SCORE_COORD_X,L"HIGH SCORE",RED);
	// "1UP"
	coordPrint(SCORE_COORD_Y+3,SCORE_COORD_X,L"1UP",RED);
	updateScore(gameStatus);
	for (int i = 0; i < gameStatus->life; i++) {
		coordPrint(SCORE_COORD_Y+21-i,SCORE_COORD_X+1,L'●',YELLOW);
	}
}

void initPathMap(wchar_t* pathMap) {

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

	for (int i = 0; i < MAP_SIZE_Y; i++) {
		wcsncpy_s(&pathMap[i*MAP_SIZE_X],MAP_SIZE_X,&map[i][0],MAP_SIZE_X);
	}
}

void updateScore(GameStatus* gameStatus) {
	coordPrint(SCORE_COORD_Y+1,SCORE_COORD_X,gameStatus->hiScore,WHITE);
	coordPrint(SCORE_COORD_Y+4,SCORE_COORD_X,gameStatus->score,WHITE);
}

void drawGameOver() {
	coordPrint(12,13,L"ＧＡＭＥ　ＯＶＥＲ",WHITE);
}

void drawStage(GameStatus* gameStatus) {
	system("cls");
	coordPrint(11,13,L"ＳＴＡＧＥ",WHITE);
	coordPrint(11,20,gameStatus->stage,WHITE);
	coordPrint(11,23,L'●',YELLOW);
	coordPrint(11,25,L'Ｘ',WHITE);
	coordPrint(11,27,gameStatus->life,WHITE);
	Sleep(2000);
}
