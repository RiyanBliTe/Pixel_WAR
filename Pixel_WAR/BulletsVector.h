#ifndef BULLETSVECTOR_H
#define BULLETSVECTOR_H

#include "Bullet.h"

/// Structure for bullets.
struct BulletsVector
{
    int size;
    int capacity;
    Bullet* bullets;
};

/// Set initial values and allocate memory for bullets vector.
/// \param vector - reference to the BulletsVector structure
void initBulletsVector(BulletsVector* vector);

/// Add new bullet structure to the vector.
/// \param vector - reference to the BulletsVector structure
/// \param bullet - new Bullet structure
void push_backBullet(BulletsVector* vector, Bullet bullet);

/// Delete bullet structure from the vector in position.
/// \param vector - reference to the BulletsVector structure
/// \param pos - position need to remove
void eraseBullet(BulletsVector* vector, int pos);

/// Free vector memory.
/// \param vector - reference to the BulletsVector structure
void deleteVector(BulletsVector* vector);

#endif // !BULLETSVECTOR_H