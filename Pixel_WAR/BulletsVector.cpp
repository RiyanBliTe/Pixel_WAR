#include "BulletsVector.h"

void initBulletsVector(BulletsVector* vector)
{
    vector->size = 0;
    vector->capacity = 10;
    vector->bullets = new Bullet[vector->capacity];
}

void push_backBullet(BulletsVector* vector, Bullet bullet)
{
    if (vector->size < vector->capacity)
    {
        vector->bullets[vector->size++] = bullet;
    }
    else
    {
        vector->capacity += 5;
        Bullet* newArray = new Bullet[vector->capacity];
        for (int i = 0; i < vector->size; i++) newArray[i] = vector->bullets[i];
        delete[] vector->bullets;
        vector->bullets = newArray;
        push_backBullet(vector, bullet);
    }
}

void eraseBullet(BulletsVector* vector, int pos)
{
    if (vector->size != 0)
    {
        if (vector->capacity > 10) vector->capacity--;
        Bullet* newArray = new Bullet[vector->capacity];
        int iter = 0;
        for (int i = 0; i < pos; i++) newArray[iter++] = vector->bullets[i];
        for (int i = pos + 1; i < vector->size; i++) newArray[iter++] = vector->bullets[i];
        delete[] vector->bullets;
        vector->bullets = newArray;
        vector->size--;
    }
}

void deleteVector(BulletsVector* vector)
{
    delete[] vector->bullets;
}