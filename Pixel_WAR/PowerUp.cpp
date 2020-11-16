#include "PowerUp.h"

#include "ControlPanel.h"

void initPowerUp(PowerUp* pwu, PU_TYPE type)
{
	pwu->x = 0;
	pwu->y = 0;
	pwu->speed = 1;
	pwu->type = type;
	pwu->EMPTY_SYMBOL = ' ';
	switch (pwu->type)
	{
	case HEALTH:
		pwu->SYMBOL = (WCHAR)9829;
		pwu->color = 0x9C;
		break;
	case WEAPON:
		pwu->SYMBOL = (WCHAR)10038;
		pwu->color = 0x96;
		break;
	default:
		break;
	}
}

void setPowerUpLocation(PowerUp* pwu, int _x, int _y)
{
	pwu->x = _x;
	pwu->y = _y;
}

void updatePowerUp(PowerUp* pwu)
{
	if (pwu->y <= GAME_HEIGHT - 5) pwu->y++;
}

bool removePowerUp(PowerUp* pwu)
{
	return pwu->y >= GAME_HEIGHT - 5 ? 1 : 0;
}