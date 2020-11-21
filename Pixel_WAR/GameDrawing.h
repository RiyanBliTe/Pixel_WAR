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

/// Drawing the game frame relative to the game state.
/// \param game - reference to the ControlPanel structure
void drawPanels(ControlPanel* game);

/// Draw text in x and y positions.
/// \param game - reference to the ControlPanel structure
/// \param text - the text you need to draw
/// \param _x - X position
/// \param _y - Y position
void drawText(ControlPanel* game, const char* text, int _x, int _y);

/// Draw numeric in x and y positions.
/// \param game - reference to the ControlPanel structure
/// \param num - the numeric you need to draw
/// \param _x - X position
/// \param _y - Y position
void drawInt(ControlPanel* game, int num, int _x, int _y);

/// Draw player.
/// \param game - reference to the ControlPanel structure
/// \param player - reference to the Player structure
/// \param type - type of button (1 - full, 0 - empty)
void draw(ControlPanel* game, Player* player, bool type);

/// Draw bullet.
/// \param game - reference to the ControlPanel structure
/// \param bullet - reference to the Bullet structure
/// \param type - type of button (1 - full, 0 - empty)
void draw(ControlPanel* game, Bullet* bullet, bool type);

/// Draw enemy.
/// \param game - reference to the ControlPanel structure
/// \param enemy - reference to the Enemy structure
/// \param type - type of button (1 - full, 0 - empty)
void draw(ControlPanel* game, Enemy* enemy, bool type);

/// Draw button.
/// \param game - reference to the ControlPanel structure
/// \param button - reference to the Button structure
/// \param type - type of button (1 - full, 0 - empty)
void draw(ControlPanel* game, Button* button, bool type);

///  Draw powerUp.
/// \param game - reference to the ControlPanel structure
/// \param pwu - reference to the powerUp structure
/// \param type - type of button (1 - full, 0 - empty)
void draw(ControlPanel* game, PowerUp* pwu, bool type);

/// Draw game logotype.
/// \param game - reference to the ControlPanel structure
/// \param _x - X position
/// \param _y - Y position
void drawLogo(ControlPanel* game, int _x, int _y);

#endif // !GAMEDRAWING_H
