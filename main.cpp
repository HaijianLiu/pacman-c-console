
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>

#include "console.h"

int main(void) {

	InitConsole();

	wchar_t str[24] = L"┏━┏━━┏━━┏━━┏━━123";

	CoordPrint(1,10,str,BLUE);

	int i = 123;

	CoordPrint(1,10,i,RED);

	getchar();
	return 0;
}
