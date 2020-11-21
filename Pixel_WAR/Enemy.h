#ifndef ENEMY_H
#define ENEMY_H

#include <chrono>
#include "Player.h"

#define ENEMY_COLOR_1 0x9A
#define ENEMY_COLOR_2 0x9E
#define ENEMY_COLOR_3 0x9C
#define ENEMY_COLOR_4 0x91

/// Moving direction for Enemy
enum eDirection
{
    TOP,
    TOP_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    BOTTOM,
    BOTTOM_LEFT,
    LEFT,
    TOP_LEFT
};

/// Enemy structure.
struct Enemy
{
    int x;
    int y;
    int dx;
    int dy;
    int type;

    int width;
    int height;

    int speed;
    int health;

    bool dead;
    bool hit;

    WORD uniqueColor;
    std::chrono::high_resolution_clock::time_point timer;

    WCHAR** ENEMY_MAP;
    WCHAR** ENEMY_EMPTY_MAP;
    WORD** COLOR_MAP;
    eDirection direction;
};

/// Set initial values and allocate memory for Enemy structure.
/// \param enemy  - reference to the Enemy structure
/// \param type
void initEnemy(Enemy* enemy, int type);

/// Calculating enemy moving
/// \param enemy - reference to the Enemy structure
void updateEnemy(Enemy* enemy);

/// Calculating next enemy direction.
/// \param dir - enemy current direction
/// \param side - side enemy
void nextDir(eDirection& dir, eDirection side);

/// Takes away life point.
/// \param enemy - reference to the Enemy structure
void hit(Enemy* enemy, int count);

/// Chek point position to enemy.
/// \param enemy - reference to the Enemy structure
/// \param _x - X coord of point
/// \param _y - Y coord of point
/// \return true - if point in field of enemy
bool inEnemy(Enemy* enemy, int _x, int _y);

/// Check player with enemy position.
/// \param enemy - reference to the Enemy structure
/// \param player - reference to the Player structure
/// \return true - if player field in enemy field
bool inEnemy(Enemy* enemy, Player* player);

/// Check enemy life for removing
/// \param enemy - reference to the Enemy structure
/// \return true - if life <= 0
bool removeEnemy(Enemy* enemy);

#endif // !ENEMY_H
