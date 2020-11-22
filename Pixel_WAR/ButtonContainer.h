#ifndef BUTTONCONTAINER_H
#define BUTTONCONTAINER_H

#include "Button.h"
#include <chrono>

/// <summary>
/// Container for the buttons.
/// </summary>
struct ButtonContainer
{
    int x;
    int y;

    int width;
    int height;

    int size;
    int capacity;

    int activePosition;
    bool pressed;

    Button* buttons;
};

/// <summary>
/// Set initial values and allocate memory for ButtonContainer structure.
/// </summary>
/// <param name="buttons"> - reference to the ButtonContainer structure</param>
void initButtonContainer(ButtonContainer* buttons);

/// <summary>
/// Set new position to the ButtonContainer.
/// </summary>
/// <param name="buttons"> - reference to the ButtonContainer structure</param>
/// <param name="_x"> - new X position</param>
/// <param name="_y"> - new Y position</param>
void setPosButtonContainer(ButtonContainer* buttons, int _x, int _y);

/// <summary>
/// Add a button to the end of the container.
/// </summary>
/// <param name="buttons"> - reference to the ButtonContainer structure</param>
/// <param name="button"> - button structure</param>
void addButton(ButtonContainer* buttons, Button button);

/// <summary>
/// Remove the button from the specific position of the container.
/// </summary>
/// <param name="buttons"> - reference to the ButtonContainer structure</param>
/// <param name="pos"> - position in container</param>
void removeButtonFromContainer(ButtonContainer* buttons, int pos);

/// <summary>
/// Free ButtonContainer memory.
/// </summary>
/// <param name="buttons"> - reference to the ButtonContainer structure</param>
void deleteBContainer(ButtonContainer* buttons);

#endif // !BUTTONCONTAINER_H