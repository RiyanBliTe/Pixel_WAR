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

/// The main structure for controlling the game "PixiWar".
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

/// Set initial values and allocate memory for all game data structures.
/// \param game - reference to the ControlPanel structure
void initPanel(ControlPanel* game);

/// Start of the game life cycle.
/// \param game - reference to the ControlPanel structure
void showGame(ControlPanel* game);

/// Set size and position of the game console.
void consoleSettings();

/// Check the activity of the keyboard keys.
/// \param game - reference to the ControlPanel structure
void checkKeys(ControlPanel* game);

/// Calculations of interaction of game objects.
/// \param game - reference to the ControlPanel structure
void gameUpdate(ControlPanel* game);

/// Painting game objects.
/// \param game - reference to the ControlPanel structure
void gameRender(ControlPanel* game);

#endif // !CONTROLPANEL_H
