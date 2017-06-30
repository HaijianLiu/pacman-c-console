
#include <stdio.h>
#include <wchar.h>

#include "console.h"
#include "level.h"


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


void initLevel(wchar_t* level) {

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
		L"━━━━┛・┃　┏━　━┓　┃・┗━━━━",
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
}
