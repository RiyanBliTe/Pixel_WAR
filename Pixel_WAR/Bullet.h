#ifndef BULLET_H
#define BULLET_H

#include <Windows.h>

#define BULLET_COLOR_1 0x9F
#define BULLET_COLOR_2 0x9E
#define BULLET_COLOR_3 0x9A
#define BULLET_COLOR_4 0x91
#define BULLET_COLOR_5 0x94

/// <summary>
/// Bullet structure.
/// </summary>
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

/// <summary>
/// Set initial values and allocate memory for bullet structure.
/// </summary>
/// <param name="bullet"> - reference to the Bullet structure</param>
/// <param name="type"> - bullet color-type</param>
void initBullet(Bullet* bullet, int type);

/// <summary>
/// Set new bullet position.
/// </summary>
/// <param name="bullet"> - reference to the Bullet structure</param>
/// <param name="_x"> - new X position</param>
/// <param name="_y"> - new Y position</param>
void setBulletLocation(Bullet* bullet, int _x, int _y);

/// <summary>
/// Calculation of the player's position.
/// </summary>
/// <param name="bullet"> - reference to the Bullet structure</param>
void updateBullet(Bullet* bullet);

/// <summary>
/// Check bullet y less then game screen
/// </summary>
/// <param name="bullet"> - reference to the Bullet structure</param>
/// <returns>true - if bullet is out of screen range</returns>
bool removeBullet(Bullet* bullet);

#endif // !BULLET_H