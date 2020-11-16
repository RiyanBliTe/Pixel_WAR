#ifndef PLAYER_H
#define PLAYER_H

#include <Windows.h>
#include <chrono>

struct Player
{
	int x;
	int y;

	int width;
	int height;

	int speed;
	int lives;
	int score;
	int weapon;

	bool up;
	bool down;
	bool left;
	bool right;
	bool firing;
	bool hit;
	std::chrono::steady_clock::time_point hitTimer;
	bool dead;

	WORD uniqueColor;
	WCHAR** PLAYER_MAP;
	char** PLAYER_EMPTY_MAP;
	WORD** PLAYER_COLOR_MAP;
};

void initPlayer(Player* player);
void setPlayerLocation(Player* player, int _x, int _y);
void updatePlayer(Player* player);
void hit(Player* player);
bool inPlayer(Player* player, int _x, int _y);

#endif // !PLAYER_H
