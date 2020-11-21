#ifndef PLAYER_H
#define PLAYER_H

#include <Windows.h>
#include <chrono>

/// Game player struct
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

/// Set initial values and allocate memory for player structure.
/// \param player - reference to the Player structure
void initPlayer(Player* player);

/// Set new player position.
/// \param player - reference to the Player structure
/// \param _x - new X position
/// \param _y - new Y position
void setPlayerLocation(Player* player, int _x, int _y);

/// Calculation of the player's position.
/// \param player - reference to the Player structure
void updatePlayer(Player* player);

/// Do a hit player and start a hitTimer.
/// \param player - reference to the Player structure
void hit(Player* player);

/// A check or point exists in the player field.
/// \param player - reference to the Player structure
/// \param _x - X need to check
/// \param _y - Y need to check
/// \return true - if point exist in player field, else - if don`t
bool inPlayer(Player* player, int _x, int _y);

#endif // !PLAYER_H
