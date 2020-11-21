#include "ButtonContainer.h"

void initButtonContainer(ButtonContainer* buttons)
{
    buttons->x = 0;
    buttons->y = 0;
    buttons->width = 0;
    buttons->height = 0;
    buttons->size = 0;
    buttons->capacity = 5;
    buttons->activePosition = 0;
    buttons->pressed = false;
    buttons->buttons = new Button[5];
}

void setPosButtonContainer(ButtonContainer* buttons, int _x, int _y)
{
    buttons->x = _x;
    buttons->y = _y;
    for (int i = 0; i < buttons->size; i++)
        setPosition(&buttons->buttons[i], buttons->buttons[i].x + _x, buttons->buttons[i].y + _y);
}

void addButton(ButtonContainer* buttons, Button button)
{
    if (buttons->size < buttons->capacity)
    {
        buttons->buttons[buttons->size++] = button;
        int maxWidth = 0;
        for (int i = 0; i < buttons->size; i++) if (buttons->buttons[i].width > maxWidth) maxWidth = buttons->buttons[i].width;
        for (int i = 0; i < buttons->size; i++) setPosition(&buttons->buttons[i], buttons->x + maxWidth / 2 - buttons->buttons[i].width / 2,
            buttons->y + i * (buttons->buttons[i].height + 2));
        buttons->width = maxWidth;
        buttons->height = buttons->buttons[0].height * buttons->size + 2 * buttons->size;
        if (buttons->size == 1) buttons->buttons[0].isActive = true;
    }
    else
    {
        buttons->capacity += 1;
        Button* newArray = new Button[buttons->capacity];
        for (int i = 0; i < buttons->size; i++) newArray[i] = buttons->buttons[i];
        delete[] buttons->buttons;
        buttons->buttons = newArray;
        addButton(buttons, button);
    }
}

void removeButtonFromContainer(ButtonContainer* buttons, int pos)
{
    if (pos >= 0 && pos < buttons->size)
        if (buttons->size != 0)
        {
            if (buttons->capacity > 10) buttons->capacity--;
            Button* newArray = new Button[buttons->capacity];
            int iter = 0;
            for (int i = 0; i < pos; i++) newArray[iter++] = buttons->buttons[i];
            for (int i = pos + 1; i < buttons->size; i++) newArray[iter++] = buttons->buttons[i];
            deleteButton(&buttons->buttons[pos]);
            delete[] buttons->buttons;
            buttons->buttons = newArray;
            buttons->size--;
        }
}

void deleteBContainer(ButtonContainer* buttons)
{
    for (int i = 0; i < buttons->size; i++) deleteButton(&buttons->buttons[i]);
    delete[] buttons->buttons;
}