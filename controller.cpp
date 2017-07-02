
#include <stdio.h>
#include <conio.h>
#include "controller.h"

int getController(int move) {
	if (_kbhit()) {
		int key = _getch();
		if (key == 0 || key == 224) { // 特殊キー
			key = _getch();
		}
		switch (key) {
			case 0x48: // up
				return KEY_UP;
			case 0x50: // down
				return KEY_DOWN;
			case 0x4B: // left
				return KEY_LEFT;
			case 0x4D: // right
				return KEY_RIGHT;
		}
	}
	return move;
}
