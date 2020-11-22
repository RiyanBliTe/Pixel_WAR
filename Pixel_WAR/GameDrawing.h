#ifndef GAMEDRAWING_H
#define GAMEDRAWING_H

#define HORIZONTAL_LINE 9552
#define VERTICAL_LINE 9553
#define LEFT_TOP_ANGLE 9556
#define RIGHT_TOP_ANGLE 9559
#define LEFT_BOTTOM_ANGLE 9562
#define RIGHT_BOTTOM_ANGLE 9565
#define HORIZONTAL_TO_TOP 9577
#define HORIZONTAL_TO_BOTTOM 9574
#define VERTICAL_TO_LEFT 9571
#define VERTICAL_TO_RIGHT 9568
#define LOGO_TEXTURE 9608

#include "ControlPanel.h"
#include "Button.h"

/// <summary>
/// Drawing the game frame relative to the game state.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
void drawPanels(ControlPanel* game);

/// <summary>
/// Draw text in x and y positions.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
/// <param name="text"> - the text you need to draw</param>
/// <param name="_x"> - X position</param>
/// <param name="_y"> - Y position</param>
void drawText(ControlPanel* game, const char* text, int _x, int _y);

/// <summary>
/// Draw numeric in x and y positions.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
/// <param name="num"> - the numeric you need to draw</param>
/// <param name="_x"> - X position</param>
/// <param name="_y"> - Y position</param>
void drawInt(ControlPanel* game, int num, int _x, int _y);

/// <summary>
/// Draw player.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
/// <param name="player"> - reference to the Player structure</param>
/// <param name="type"> - type of button (1 - full, 0 - empty)</param>
void draw(ControlPanel* game, Player* player, bool type);

/// <summary>
/// Draw bullet.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
/// <param name="bullet"> - reference to the Bullet structure</param>
/// <param name="type"> - type of button (1 - full, 0 - empty)</param>
void draw(ControlPanel* game, Bullet* bullet, bool type);

/// <summary>
/// Draw enemy.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
/// <param name="enemy"> - reference to the Enemy structure</param>
/// <param name="type"> - type of button (1 - full, 0 - empty)</param>
void draw(ControlPanel* game, Enemy* enemy, bool type);

/// <summary>
/// Draw button.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
/// <param name="button"> - reference to the Button structure</param>
/// <param name="type"> - type of button (1 - full, 0 - empty)</param>
void draw(ControlPanel* game, Button* button, bool type);

/// <summary>
/// Draw powerUp.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
/// <param name="pwu"> - reference to the powerUp structure</param>
/// <param name="type"> - type of button (1 - full, 0 - empty)</param>
void draw(ControlPanel* game, PowerUp* pwu, bool type);

/// <summary>
/// Draw game logotype.
/// </summary>
/// <param name="game"> - reference to the ControlPanel structure</param>
/// <param name="_x"> - X position</param>
/// <param name="_y"> - Y position</param>
void drawLogo(ControlPanel* game, int _x, int _y);

#endif // !GAMEDRAWING_H
