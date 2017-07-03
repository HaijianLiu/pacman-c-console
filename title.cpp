
#include <stdio.h>
#include <windows.h>
#include <wchar.h>

#include "title.h"
#include "console.h"
#include "controller.h"

void drawTutorial() {
	coordPrint(11,12,L"方向：←↑↓→　決定：ＥＮＴＥＲ",WHITE);
	getchar();
}


void initTitle(wchar_t* titleText) {

	wchar_t text[TITLE_SIZE_Y][TITLE_SIZE_X] = {
		L"┏━━━━┓　┏━━━━━┓┏━━━━━┓┏━━━━┓",
		L"┃・・・・┗┓┃・・・・・┃┃・・・・・┃┃・・・・┃",
		L"┃・┏━┓・┃┃・┏━┓・┃┗━┓・┏━┛┃・┏━━┛",
		L"┃・┃　┃・┃┃・┃　┃・┃　　┃・┃　　┃・┗━━┓",
		L"┃・┃　┃・┃┃・┃　┃・┃　　┃・┃　　┃・・・・┃",
		L"┃・┃　┃・┃┃・┃　┃・┃　　┃・┃　　┗━━┓・┃",
		L"┃・┗━┛・┃┃・┗━┛・┃　　┃・┃　　┏━━┛・┃",
		L"┃・・・・┏┛┃・・・・・┃　　┃・┃　　┃・・・・┃",
		L"┗━━━━┛　┗━━━━━┛　　┗━┛　　┗━━━━┛",
	};

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

	coordPrint(TEXT_COORD_Y,TEXT_COORD_X,L"ＮＯＲＭＡＬ",YELLOW);
	coordPrint(TEXT_COORD_Y,TEXT_COORD_X+8,L"ＨＡＲＤ",GRAY);
	coordPrint(TEXT_COORD_Y,TEXT_COORD_X+14,L"ＡＫＵＭＵ",GRAY);

}


void updateTitle(wchar_t* titleText, GameStatus* gameStatus) {
	int count = 0;
	bool press = false;
	int select = 0;
	int key = 0;
	while (!press) {
		// title animation
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
		// input key
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
		// update select
		switch (select) {
			case 0:
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X,L"ＮＯＲＭＡＬ",YELLOW);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+8,L"ＨＡＲＤ",GRAY);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+14,L"ＡＫＵＭＵ",GRAY);
				break;
			case 1:
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X,L"ＮＯＲＭＡＬ",GRAY);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+8,L"ＨＡＲＤ",YELLOW);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+14,L"ＡＫＵＭＵ",GRAY);
				break;
			case 2:
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X,L"ＮＯＲＭＡＬ",GRAY);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+8,L"ＨＡＲＤ",GRAY);
				coordPrint(TEXT_COORD_Y,TEXT_COORD_X+14,L"ＡＫＵＭＵ",YELLOW);
				break;
		}

		count ++;
		Sleep(100);
	}
	gameStatus->hardness = select;
}
