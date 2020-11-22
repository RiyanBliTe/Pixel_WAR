#ifndef BUTTON_H
#define BUTTON_H

#include <Windows.h>
#include <chrono>

/// <summary>
/// Game button struct.
/// </summary>
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

/// <summary>
/// Set initial values and allocate memory for button structure.
/// </summary>
/// <param name="button"> - reference to the Button structure</param>
/// <param name="title"> - button text</param>
void initButton(Button* button, const char* title);

/// <summary>
/// Set new button position.
/// </summary>
/// <param name="button"> - reference to the Button structure</param>
/// <param name="_x"> - new X position</param>
/// <param name="_y"> - new Y position</param>
void setPosition(Button* button, int _x, int _y);

/// <summary>
/// Free button memory.
/// </summary>
/// <param name="button"> - reference to the Button structure</param>
void deleteButton(Button* button);

#endif // !BUTTON_H
