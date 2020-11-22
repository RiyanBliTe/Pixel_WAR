#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#define GAME_WIDTH 200
#define GAME_HEIGHT 60

#include "Player.h"
#include "BulletsVector.h"
#include "Bullet.h"
#include "EnemyVector.h"
#include "Enemy.h"
#include "PowerUpVector.h"
#include "PowerUp.h"
#include "ButtonContainer.h"
#include "Button.h"

#include <Windows.h>
#include <chrono>

enum STATES { MENU, GAME };

/// <summary>
/// The main structure for controlling the game "PixiWar".
/// </summary>
struct ControlPanel
{
    bool mainLoop;
    bool menuLoop;
    bool gameLoop;
    bool playerRedraw;
    bool gamePressed;

    int gameCount;

    std::chrono::high_resolution_clock::time_point timer;
    std::chrono::high_resolution_clock::time_point firingTimer;
    long firingDelay;

    STATES state;

    Player player;
    BulletsVector bullets;
    EnemyVector enemies;
    EnemyVector menuEnemies;
    PowerUpVector powerUps;
    ButtonContainer buttons;

    WORD gameColor;
    WORD hitColor;
    CHAR_INFO gameMap[GAME_HEIGHT][GAME_WIDTH];
};

/// <summary>
/// Set initial values and allocate memory for all game data structures.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
void initPanel(ControlPanel* game);

/// <summary>
/// Start of the game life cycle.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
void showGame(ControlPanel* game);

/// <summary>
/// Set size and position of the game console.
/// </summary>
void consoleSettings();

/// <summary>
/// Check the activity of the keyboard keys.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
void checkKeys(ControlPanel* game);

/// <summary>
/// Calculations of interaction of game objects.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
void gameUpdate(ControlPanel* game);

/// <summary>
/// Painting game objects.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
void gameRender(ControlPanel* game);

#endif // !CONTROLPANEL_H
