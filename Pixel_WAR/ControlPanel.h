#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#define GAME_WIDTH 200
#define GAME_HEIGHT 60

#include "Player.h"
#include "BulletsVector.h"
#include "Bullet.h"
#include "EnemyVector.h"
#include "Enemy.h"
#include "Button.h"
#include "PowerUpVector.h"
#include "PowerUp.h"

#include <Windows.h>
#include <chrono>

struct ControlPanel
{
	bool mainLoop;
	bool menuLoop;
	bool gameLoop;
	bool playerRedraw;

	std::chrono::steady_clock::time_point timer;
	std::chrono::steady_clock::time_point firingTimer;
	long firingDelay;
	
	enum STATES { MENU, GAME } state;

	Player player;
	BulletsVector bullets;
	EnemyVector enemies;
	PowerUpVector powerUps;

	WORD gameColor;
	WORD hitColor;
	CHAR_INFO gameMap[GAME_HEIGHT][GAME_WIDTH];
};

void initPanel(ControlPanel* game);
void showGame(ControlPanel* game);
void consoleSettings();
void checkKeys(ControlPanel* game);

void gameUpdate(ControlPanel* game);
void gameRender(ControlPanel* game);

void drawPanels(ControlPanel* game);
void drawText(ControlPanel* game, const char* text, int _x, int _y);
void drawInt(ControlPanel* game, int num, int _x, int _y);
void draw(ControlPanel* game, Player* player, bool type);
void draw(ControlPanel* game, Bullet* bullet, bool type);
void draw(ControlPanel* game, Enemy* enemy, bool type);
void draw(ControlPanel* game, Button* button);
void draw(ControlPanel* game, PowerUp* pwu, bool type);

#endif // !CONTROLPANEL_H
