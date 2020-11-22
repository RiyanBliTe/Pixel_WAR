#ifndef BULLETSVECTOR_H
#define BULLETSVECTOR_H

#include "Bullet.h"

/// <summary>
/// Structure for bullets.
/// </summary>
struct BulletsVector
{
    int size;
    int capacity;
    Bullet* bullets;
};

/// <summary>
/// Set initial values and allocate memory for bullets vector.
/// </summary>
/// <param name="vector"> - reference to the BulletsVector structure</param>
void initBulletsVector(BulletsVector* vector);

/// <summary>
/// Add new bullet structure to the vector.
/// </summary>
/// <param name="vector"> - reference to the BulletsVector structure</param>
/// <param name="bullet"> - new Bullet structure</param>
void push_backBullet(BulletsVector* vector, Bullet bullet);

/// <summary>
/// Delete bullet structure from the vector in position.
/// </summary>
/// <param name="vector"> - reference to the BulletsVector structure</param>
/// <param name="pos"> - position need to remove</param>
void eraseBullet(BulletsVector* vector, int pos);

/// <summary>
/// Free vector memory.
/// </summary>
/// <param name="vector"> - reference to the BulletsVector structure</param>
void deleteVector(BulletsVector* vector);

#endif // !BULLETSVECTOR_H