#ifndef ENEMY_H
#define ENEMY_H

#include <chrono>
#include "Player.h"

#define ENEMY_COLOR_1 0x9A
#define ENEMY_COLOR_2 0x9E
#define ENEMY_COLOR_3 0x9C
#define ENEMY_COLOR_4 0x91

enum eDirection
{
	TOP,
	TOP_RIGHT,
	RIGHT,
	BOTTOM_RIGHT,
	BOTTOM,
	BOTTOM_LEFT,
	LEFT,
	TOP_LEFT
};

struct Enemy
{
	int x;
	int y;
	int dx;
	int dy;
	int type;

	int width;
	int height;
	
	int speed;
	int health;
	
	bool dead;
	bool hit;

	WORD uniqueColor;
	std::chrono::steady_clock::time_point timer;
	
	WCHAR** ENEMY_MAP;
	WCHAR** ENEMY_EMPTY_MAP;
	WORD** COLOR_MAP;
	eDirection direction;
};

void initEnemy(Enemy* enemy, int type);
void updateEnemy(Enemy* enemy);
void nextDir(eDirection& dir, eDirection side);
void hit(Enemy* enemy);
bool inEnemy(Enemy* enemy, int _x, int _y);
bool inEnemy(Enemy* enemy, Player* player);
bool removeEnemy(Enemy* enemy);

#endif // !ENEMY_H
