
#ifndef _TITLE_H_
#define _TITLE_H_

#include "level.h"

#define TITLE_SIZE_X (28)
#define TITLE_SIZE_Y (9)
#define TITLE_COORD_X (6)
#define TITLE_COORD_Y (6)
#define TEXT_COORD_X (10)
#define TEXT_COORD_Y (17)

void drawTutorial();
void initTitle(wchar_t* titleText);
void updateTitle(wchar_t* titleText, GameStatus* gameStatus);

#endif
