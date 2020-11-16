#ifndef BULLET_H
#define BULLET_H

#include <Windows.h>

#define BULLET_COLOR_1 0x9F
#define BULLET_COLOR_2 0x9E
#define BULLET_COLOR_3 0x9A
#define BULLET_COLOR_4 0x91
#define BULLET_COLOR_5 0x94

struct Bullet
{
	int x;
	int y;
	int speed;
	WORD uniqueColor;
	WCHAR BULLET;
	WCHAR EMPTY_BULLET;
};

void initBullet(Bullet* bullet, int type);
void setBulletLocation(Bullet* bullet, int _x, int _y);
void updateBullet(Bullet* bullet);
bool removeBullet(Bullet* bullet);

#endif // !BULLET_H