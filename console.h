﻿
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#define BLUE   (9)
#define YELLOW (14)
#define RED    (12)
#define WHITE  (7)
#define PINK  (13)
#define CYAN  (11)
#define GREEN  (10)
#define GRAY  (8)


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

// コンソールを初期化
void initConsole();

// 文字を表示（座標：x,y  色：color）
void coordPrint(int y, int x, wchar_t* str, int color);
void coordPrint(int y, int x, wchar_t ch, int color);
// 数字を表示（座標：x,y  色：color）
void coordPrint(int y, int x, int num, int color);


#endif
