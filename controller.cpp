
/*==============================================================================
controller.cpp　入力プログラム
Author　　　　　　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/

/*==============================================================================
インクルードファイル
==============================================================================*/
#include <stdio.h>
#include <conio.h>
#include "controller.h"

/*==============================================================================
入力キーの取得
==============================================================================*/
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
			case 0x0D: // right
				return KEY_ENTER;
		}
	}
	return move;
}

/*==============================================================================
入力キーの取得
==============================================================================*/
int getController() {
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
			case 0x0D: // right
				return KEY_ENTER;
		}
	}
	return 0;
}
