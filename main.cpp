
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

	for (int i = 0; i < MAP_SIZE_Y; i++) {
		coordPrint(i, 0, &level[i * MAP_SIZE_X], BLUE);
	}

	getchar();
	return 0;
}
