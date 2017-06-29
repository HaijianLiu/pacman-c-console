
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>

int main(void) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD savedAttributes;
	COORD coord = {10,10};

	GetConsoleScreenBufferInfo(hConsole,&consoleInfo);
	savedAttributes = consoleInfo.wAttributes;

	SetConsoleTextAttribute(hConsole,12);

	setlocale(LC_CTYPE, "");
	wchar_t str[24] = L"┏━┏━━┏━━┏━━┏━━";
	wprintf(L"%s\n",&str[1]);
	SetConsoleTextAttribute(hConsole,13);

	wprintf(L"%s\n",&str[1]);

	SetConsoleTextAttribute(hConsole,15);
	wprintf(L"%s\n",&str[1]);

	SetConsoleCursorPosition(hConsole,coord);

	CONSOLE_CURSOR_INFO consoleCursorInfo;
	GetConsoleCursorInfo(hConsole,&consoleCursorInfo);
	consoleCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsole,&consoleCursorInfo);

/*
Color         Background Foreground
---------------------------------------------
Black            0           0
Blue             1           1
Green            2           2
Cyan             3           3
Red              4           4
Magenta          5           5
Brown            6           6
White            7           7
Gray             -           8
Intense Blue     -           9
Intense Green    -           10
Intense Cyan     -           11
Intense Red      -           12
Intense Magenta  -           13
Yellow           -           14
Intense White    -           15
*/


	getchar();
	return 0;
}
