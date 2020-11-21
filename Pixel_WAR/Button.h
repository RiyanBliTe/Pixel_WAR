#ifndef BUTTON_H
#define BUTTON_H

#include <Windows.h>
#include <chrono>

/// Game button struct.
struct Button
{
    int x;
    int y;

    int width;
    int height;

    bool isActive;

    char* title;

    std::chrono::high_resolution_clock::time_point timer;

    WORD uniqueColor;
    WCHAR** BUTTON_MAP;
    WCHAR** BUTTON_EMPTY_MAP;
};

/// Set initial values and allocate memory for button structure.
/// \param button - reference to the Button structure
/// \param title - button text
void initButton(Button* button, const char* title);

/// Set new button position.
/// \param button - reference to the Button structure
/// \param _x - new X position
/// \param _y - new Y position
void setPosition(Button* button, int _x, int _y);

/// Free button memory.
/// \param button - reference to the Button structure
void deleteButton(Button* button);

#endif // !BUTTON_H
