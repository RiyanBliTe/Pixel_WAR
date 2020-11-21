#ifndef BULLET_H
#define BULLET_H

#include <Windows.h>

#define BULLET_COLOR_1 0x9F
#define BULLET_COLOR_2 0x9E
#define BULLET_COLOR_3 0x9A
#define BULLET_COLOR_4 0x91
#define BULLET_COLOR_5 0x94

/// Bullet structure.
struct Bullet
{
    int x;
    int y;
    int speed;
    int type;
    WORD uniqueColor;
    WCHAR BULLET;
    WCHAR EMPTY_BULLET;
};

/// Set initial values and allocate memory for bullet structure.
/// \param bullet - reference to the Bullet structure
/// \param type - bullet color-type
void initBullet(Bullet* bullet, int type);

/// Set new bullet position.
/// \param bullet - reference to the Bullet structure
/// \param _x - new X position
/// \param _y - new Y position
void setBulletLocation(Bullet* bullet, int _x, int _y);

/// Calculation of the player's position.
/// \param bullet - reference to the Bullet structure
void updateBullet(Bullet* bullet);

/// Check bullet y less then game screen
/// \param bullet - reference to the Bullet structure
/// \return true - if bullet is out of screen range
bool removeBullet(Bullet* bullet);

#endif // !BULLET_H