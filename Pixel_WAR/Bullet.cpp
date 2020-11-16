#include "Bullet.h"

void initBullet(Bullet* bullet, int type)
{
	bullet->x = 0;
	bullet->y = 0;
	bullet->speed = 0;
	bullet->BULLET = (WCHAR)'|';
	bullet->EMPTY_BULLET = (WCHAR)' ';

	switch (type)
	{
	case 1:
		bullet->uniqueColor = BULLET_COLOR_1;
		break;
	case 2:
		bullet->uniqueColor = BULLET_COLOR_2;
		break;
	case 3:
		bullet->uniqueColor = BULLET_COLOR_3;
		break;
	case 4:
		bullet->uniqueColor = BULLET_COLOR_4;
		break;
	case 5:
		bullet->uniqueColor = BULLET_COLOR_5;
		break;
	default:
		break;
	}
}

void setBulletLocation(Bullet* bullet, int _x, int _y)
{
	bullet->x = _x;
	bullet->y = _y;
}

void updateBullet(Bullet* bullet)
{
	if (bullet->y > 1) bullet->y--;
}

bool removeBullet(Bullet* bullet)
{
	return bullet->y <= 1 ? 1 : 0;
}
