
#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef struct{
	int x, y, move, color, counter;
	bool super, alive;
	wchar_t maker[2];
}PLAYER;

PLAYER initPlayer();

void movePlayer(PLAYER* player, wchar_t* level);

void updatePlayer(PLAYER* player, wchar_t* level);

#endif
