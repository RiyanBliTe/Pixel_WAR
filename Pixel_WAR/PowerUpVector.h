#ifndef POWERUPVECTOR_H
#define POWERUPVECTOR_H

#include "PowerUp.h"

/// Structure for powerUps.
struct PowerUpVector
{
    int size;
    int capacity;
    PowerUp* pwus;
};

/// Set initial values and allocate memory for powerUps vector.
/// \param vector - reference to the PowerUpVector structure
void initPWUVector(PowerUpVector* vector);

/// Add new powerUp structure to the vector.
/// \param vector - reference to the BulletsVector structure
/// \param pwu - new powerUp structure
void push_backPowerUp(PowerUpVector* vector, PowerUp pwu);

/// Delete powerUp structure from the vector in position.
/// \param vector - reference to the BulletsVector structure
/// \param pos - position need to remove
void erasePowerUp(PowerUpVector* vector, int pos);

/// Free vector memory.
/// \param vector - reference to the BulletsVector structure
void deleteVector(PowerUpVector* vector);

#endif // !POWERUPVECTOR_H