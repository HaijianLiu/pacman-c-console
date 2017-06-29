
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>

#include "console.h"
#include "level.h"


int main(void) {

	initConsole();

	wchar_t level[MAP_SIZE_X * MAP_SIZE_Y] = {};
	getLevel(level);

	// coordPrint(1,20,1,RED);


	getchar();
	return 0;
}
