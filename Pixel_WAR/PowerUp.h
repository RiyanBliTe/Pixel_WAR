#ifndef POWERUP_H
#define POWERUP_H

#include <Windows.h>

/// <summary>
/// PowerUp type.
/// </summary>
enum PU_TYPE { HEALTH, WEAPON };

/// <summary>
/// PowerUp structure.
/// </summary>
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

/// <summary>
/// Set initial values and allocate memory for PowerUp structure.
/// </summary>
/// <param name="pwu"> - reference to the PowerUp structure</param>
/// <param name="type"> - type of PowerUp</param>
void initPowerUp(PowerUp* pwu, PU_TYPE type);

/// <summary>
/// Calculating powerUp moving.
/// </summary>
/// <param name="pwu"> - reference to the Bullet structure</param>
void updatePowerUp(PowerUp* pwu);

/// <summary>
/// Set new location to powerUp.
/// </summary>
/// <param name="pwu"> - reference to the Bullet structure</param>
/// <param name="_x"> - new X location</param>
/// <param name="_y"> - new Y location</param>
void setPowerUpLocation(PowerUp* pwu, int _x, int _y);

/// <summary>
/// Check if need to delete powerUp.
/// </summary>
/// <param name="pwu"> - reference to the Bullet structure</param>
/// <returns>true - if out of screen</returns>
bool removePowerUp(PowerUp* pwu);

#endif // !POWERUP_H
