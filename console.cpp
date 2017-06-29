
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>

#include "console.h"

HANDLE hConsole;
CONSOLE_SCREEN_BUFFER_INFO consoleScreenInfo;

void initConsole() {
	// コンソールhandleを取得
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// cursorを表示しない
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	GetConsoleCursorInfo(hConsole,&consoleCursorInfo);
	consoleCursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole,&consoleCursorInfo);
	// コンソールバファを取得
	GetConsoleScreenBufferInfo(hConsole,&consoleScreenInfo);
	// 文字コードを変更
	setlocale(LC_CTYPE,"");
}

void coordPrint(int y, int x, wchar_t* str, int color) {
	COORD coord = {2*x,y};                    // 座標を設定
	SetConsoleCursorPosition(hConsole,coord); // 座標を更新
	SetConsoleTextAttribute (hConsole,color); // 色を設定
	wprintf(L"%s",str);                       // 文字を出力
	SetConsoleCursorPosition(hConsole,{0,0}); // 座標をリセット
	SetConsoleTextAttribute (hConsole,0);     // 色をリセット
}

void coordPrint(int y, int x, wchar_t ch, int color) {
	COORD coord = {2*x,y};                    // 座標を設定
	SetConsoleCursorPosition(hConsole,coord); // 座標を更新
	SetConsoleTextAttribute (hConsole,color); // 色を設定
	wprintf(L"%c",ch);                        // 文字を出力
	SetConsoleCursorPosition(hConsole,{0,0}); // 座標をリセット
	SetConsoleTextAttribute (hConsole,0);     // 色をリセット
}

void coordPrint(int y, int x, int num, int color) {
	COORD coord = {2*x,y};                    // 座標を設定
	SetConsoleCursorPosition(hConsole,coord); // 座標を更新
	SetConsoleTextAttribute (hConsole,color); // 色を設定
	wprintf(L"%d",num);                       // 数字を出力
	SetConsoleCursorPosition(hConsole,{0,0}); // 座標をリセット
	SetConsoleTextAttribute (hConsole,0);     // 色をリセット
}
