#ifndef ENEMY_H
#define ENEMY_H

#include <chrono>
#include "Player.h"

#define ENEMY_COLOR_1 0x9A
#define ENEMY_COLOR_2 0x9E
#define ENEMY_COLOR_3 0x9C
#define ENEMY_COLOR_4 0x91

/// <summary>
/// Moving direction for Enemy
/// </summary>
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

/// <summary>
/// Enemy structure.
/// </summary>
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

/// <summary>
/// Set initial values and allocate memory for Enemy structure.
/// </summary>
/// <param name="enemy"> - reference to the Enemy structure</param>
/// <param name="type"> - type of enemy</param>
void initEnemy(Enemy* enemy, int type);

/// <summary>
/// Calculating enemy moving
/// </summary>
/// <param name="enemy"> - reference to the Enemy structure</param>
void updateEnemy(Enemy* enemy);

/// <summary>
/// Calculating next enemy direction.
/// </summary>
/// <param name="dir"> - enemy current direction</param>
/// <param name="side"> - side enemy</param>
void nextDir(eDirection& dir, eDirection side);

/// <summary>
/// Takes away life point.
/// </summary>
/// <param name="enemy"> - reference to the Enemy structure</param>
/// <param name="count"> - count of hit</param>
void hit(Enemy* enemy, int count);

/// Chek point position to enemy.
/// \param enemy - reference to the Enemy structure
/// \param _x - X coord of point
/// \param _y - Y coord of point
/// \return true - if point in field of enemy

/// <summary>
/// Chek point position to enemy.
/// </summary>
/// <param name="enemy"> - reference to the Enemy structure</param>
/// <param name="_x"> - X coord of point</param>
/// <param name="_y"> - Y coord of point</param>
/// <returns>true - if point in field of enemy</returns>
bool inEnemy(Enemy* enemy, int _x, int _y);

/// <summary>
/// Check player with enemy position.
/// </summary>
/// <param name="enemy"> - reference to the Enemy structure</param>
/// <param name="player"> - reference to the Player structure</param>
/// <returns>true - if player field in enemy field</returns>
bool inEnemy(Enemy* enemy, Player* player);

/// <summary>
/// Check enemy life for removing
/// </summary>
/// <param name="enemy"> - reference to the Enemy structure</param>
/// <returns>true - if life <= 0</returns>
bool removeEnemy(Enemy* enemy);

#endif // !ENEMY_H
