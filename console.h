
/*==============================================================================
console.h　コンソールパラメータヘッダー
Author　　　GP-11A-243 (40) LIU HAIJIAN
==============================================================================*/
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

/*==============================================================================
マクロ定義
==============================================================================*/
// 文字の色
#define WHITE  (7)
#define GRAY   (8)
#define BLUE   (9)
#define GREEN  (10)
#define CYAN   (11)
#define RED    (12)
#define PINK   (13)
#define YELLOW (14)

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

/*==============================================================================
プロトタイプ宣言
==============================================================================*/
void initConsole();
void coordPrint(int y, int x, wchar_t* str, int color);
void coordPrint(int y, int x, wchar_t ch, int color);
void coordPrint(int y, int x, int num, int color);


#endif
