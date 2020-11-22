#ifndef PLAYER_H
#define PLAYER_H

#include <Windows.h>
#include <chrono>
/// <summary>
/// Game player struct.
/// </summary>
struct Player
{
    int x;
    int y;

    int width;
    int height;

    int speed;
    int lives;
    int score;
    int weapon;

    bool up;
    bool down;
    bool left;
    bool right;
    bool firing;
    bool hit;
    std::chrono::high_resolution_clock::time_point hitTimer;
    bool dead;

    WORD uniqueColor;
    WCHAR** PLAYER_MAP;
    WCHAR** PLAYER_EMPTY_MAP;
    WORD** PLAYER_COLOR_MAP;
};

/// <summary>
/// Set initial values and allocate memory for player structure.
/// </summary>
/// <param name="player"> - reference to the Player structure</param>
void initPlayer(Player* player);

/// <summary>
/// Set new player position.
/// </summary>
/// <param name="player"> - reference to the Player structure</param>
/// <param name="_x"> - new X position</param>
/// <param name="_y"> - new Y position</param>
void setPlayerLocation(Player* player, int _x, int _y);

/// <summary>
/// Calculation of the player's position.
/// </summary>
/// <param name="player"> - reference to the Player structure</param>
void updatePlayer(Player* player);

/// <summary>
/// Do a hit player and start a hitTimer.
/// </summary>
/// <param name="player"> - reference to the Player structure</param>
void hit(Player* player);

/// <summary>
/// A check or point exists in the player field.
/// </summary>
/// <param name="player"> - reference to the Player structure</param>
/// <param name="_x"> - X need to check</param>
/// <param name="_y"> - Y need to check</param>
/// <returns>true - if point exist in player field, else - if don`t</returns>
bool inPlayer(Player* player, int _x, int _y);

#endif // !PLAYER_H
