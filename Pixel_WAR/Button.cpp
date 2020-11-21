#include "Button.h"
#include "GameDrawing.h"


void initButton(Button* button, const char* title)
{
    button->x = 0;
    button->y = 0;
    button->title = new char[strlen(title) + 1];
    strcpy_s(button->title, strlen(title) + 1, title);
    button->width = strlen(title) + 8;
    button->height = 3;
    button->timer = std::chrono::high_resolution_clock::now();
    button->uniqueColor = 0xF1;
    button->isActive = false;
    button->BUTTON_MAP = new WCHAR * [button->height];
    for (int i = 0; i < button->height; i++)
    {
        button->BUTTON_MAP[i] = new WCHAR[button->width];
        for (int j = 0; j < button->width; j++) button->BUTTON_MAP[i][j] = ' ';
    }

    button->BUTTON_MAP[0][0] = (WCHAR)LEFT_TOP_ANGLE;
    button->BUTTON_MAP[0][button->width - 1] = (WCHAR)RIGHT_TOP_ANGLE;
    button->BUTTON_MAP[button->height - 1][0] = (WCHAR)LEFT_BOTTOM_ANGLE;
    button->BUTTON_MAP[button->height - 1][button->width - 1] = (WCHAR)RIGHT_BOTTOM_ANGLE;
    for (int i = 0; i < button->width - 2; i++)
    {
        button->BUTTON_MAP[0][i + 1] = (WCHAR)HORIZONTAL_LINE;
        button->BUTTON_MAP[button->height - 1][i + 1] = (WCHAR)HORIZONTAL_LINE;
    }
    for (int i = 0; i < button->width - 8; i++) button->BUTTON_MAP[1][i + 4] = button->title[i];

    button->BUTTON_EMPTY_MAP = new WCHAR * [button->height];
    for (int i = 0; i < button->height; i++)
    {
        button->BUTTON_EMPTY_MAP[i] = new WCHAR[button->width];
        for (int j = 0; j < button->width; j++)
            button->BUTTON_EMPTY_MAP[i][j] = ' ';
    }
}

void setPosition(Button* button, int _x, int _y)
{
    button->x = _x;
    button->y = _y;
}

void deleteButton(Button* button)
{
    delete[] button->title;
    delete[] button->BUTTON_MAP;
    delete[] button->BUTTON_EMPTY_MAP;
}