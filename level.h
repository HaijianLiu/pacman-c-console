
#ifndef _LEVEL_H_
#define _LEVEL_H_


#define MAP_SIZE_X (22)
#define MAP_SIZE_Y (25)
#define SCREEN_LEFT (7)
#define SCORE_COORD_X (SCREEN_LEFT + MAP_SIZE_X)
#define SCORE_COORD_Y (1)

#define SCORE_DOT_S (10)
#define SCORE_DOT_B (50)

#define NORMAL (180)
#define HARD (240)
#define ENEMY_GROUP (4)

typedef struct {
	int score;
} GameStatus;

GameStatus initGameStatus();

void initItem(wchar_t* level);

void initLevel(wchar_t* map, GameStatus* gameStatus);

void initPathMap(wchar_t* pathMap);

void updateScore(GameStatus* gameStatus);


#endif
