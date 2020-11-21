#ifndef POWERUP_H
#define POWERUP_H

#include <Windows.h>

/// PowerUp type
enum PU_TYPE { HEALTH, WEAPON };

/// PowerUp structure.
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

/// Set initial values and allocate memory for PowerUp structure.
/// \param pwu - reference to the PowerUp structure
/// \param type - type of PowerUp
void initPowerUp(PowerUp* pwu, PU_TYPE type);

/// Calculating powerUp moving.
/// \param pwu - reference to the Bullet structure
void updatePowerUp(PowerUp* pwu);

/// Set new location to powerUp.
/// \param pwu - reference to the Bullet structure
/// \param _x - new X location
/// \param _y - new Y location
void setPowerUpLocation(PowerUp* pwu, int _x, int _y);

/// Check if need to delete powerUp.
/// \param pwu - reference to the Bullet structure
/// \return true - if out of screen
bool removePowerUp(PowerUp* pwu);

#endif // !POWERUP_H
