#ifndef BUTTONCONTAINER_H
#define BUTTONCONTAINER_H

#include "Button.h"
#include <chrono>

/// Container for the buttons
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

/// Set initial values and allocate memory for ButtonContainer structure.
/// \param buttons - reference to the ButtonContainer structure
void initButtonContainer(ButtonContainer* buttons);

/// Set new position to the ButtonContainer.
/// \param buttons - reference to the ButtonContainer structure
/// \param _x - new X position
/// \param _y - new Y position
void setPosButtonContainer(ButtonContainer* buttons, int _x, int _y);

/// Add a button to the end of the container.
/// \param buttons - reference to the ButtonContainer structure
/// \param button - button structure
void addButton(ButtonContainer* buttons, Button button);

/// Remove the button from the specific position of the container.
/// \param buttons - reference to the ButtonContainer structure
/// \param pos - position in container
void removeButtonFromContainer(ButtonContainer* buttons, int pos);

/// Free ButtonContainer memory.
/// \param buttons - reference to the ButtonContainer structure
void deleteBContainer(ButtonContainer* buttons);

#endif // !BUTTONCONTAINER_H