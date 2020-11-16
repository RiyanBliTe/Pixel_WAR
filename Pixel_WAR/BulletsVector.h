#ifndef BULLETSVECTOR_H
#define BULLETSVECTOR_H

#include "Bullet.h"

struct BulletsVector
{
	int size;
	int capacity;
	Bullet* bullets;
};

void initBulletsVector(BulletsVector* vector);
void push_backBullet(BulletsVector* vector, Bullet bullet);
void eraseBullet(BulletsVector* vector, int pos);
void deleteVector(BulletsVector* vector);

#endif // !BULLETSVECTOR_H