
#include <stdio.h>
#include <wchar.h>

#include "level.h"
#include "console.h"

GameStatus initGameStatus() {
	GameStatus gameStatus;
	gameStatus.score = 0;
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

}

void initPathMap(wchar_t* pathMap) {

	wchar_t map[MAP_SIZE_Y][MAP_SIZE_X] = {
		L"┏━━━━━━━━━┳━━━━━━━━━┓",
		L"┃□　　　■　　　□┃□　　　■　　　□┃",
		L"┃　┏━┓　┏━┓　┃　┏━┓　┏━┓　┃",
		L"┃　┃　┃　┃　┃　┃　┃　┃　┃　┃　┃",
		L"┃　┗━┛　┗━┛　┃　┗━┛　┗━┛　┃",
		L"┃■　　　■　■　■　■　■　■　　　■┃",
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
	coordPrint(SCORE_COORD_Y+1,SCORE_COORD_X,gameStatus->score,WHITE);
	coordPrint(SCORE_COORD_Y+4,SCORE_COORD_X,gameStatus->score,WHITE);
}
