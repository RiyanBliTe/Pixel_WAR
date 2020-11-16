#ifndef POWERUP_H
#define POWERUP_H

#include <Windows.h>

enum PU_TYPE { HEALTH, WEAPON };

struct PowerUp
{
	int x;
	int y;

	PU_TYPE type;
	int speed;
	WORD color;

	WCHAR SYMBOL;
	WCHAR EMPTY_SYMBOL;
};

void initPowerUp(PowerUp* pwu, PU_TYPE type);
void updatePowerUp(PowerUp* pwu);
void setPowerUpLocation(PowerUp* pwu, int _x, int _y);
bool removePowerUp(PowerUp* pwu);

#endif // !POWERUP_H
