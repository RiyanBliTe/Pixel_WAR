#ifndef POWERUPVECTOR_H
#define POWERUPVECTOR_H

#include "PowerUp.h"

/// <summary>
/// Structure for powerUps.
/// </summary>
struct PowerUpVector
{
    int size;
    int capacity;
    PowerUp* pwus;
};

/// <summary>
/// Set initial values and allocate memory for powerUps vector.
/// </summary>
/// <param name="vector"> - reference to the PowerUpVector structure</param>
void initPWUVector(PowerUpVector* vector);

/// <summary>
/// Add new powerUp structure to the vector.
/// </summary>
/// <param name="vector"> - reference to the BulletsVector structure</param>
/// <param name="pwu"> - new powerUp structure</param>
void push_backPowerUp(PowerUpVector* vector, PowerUp pwu);

/// <summary>
/// Delete powerUp structure from the vector in position.
/// </summary>
/// <param name="vector"> - reference to the BulletsVector structure</param>
/// <param name="pos"> - position need to remove</param>
void erasePowerUp(PowerUpVector* vector, int pos);

/// <summary>
/// Free vector memory.
/// </summary>
/// <param name="vector"> - reference to the BulletsVector structure</param>
void deleteVector(PowerUpVector* vector);

#endif // !POWERUPVECTOR_H