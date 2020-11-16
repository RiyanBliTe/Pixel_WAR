#include "Button.h"

void initButton(Button* button, const char* title)
{
	button->x = 0;
	button->y = 0;
	button->title = new char[strlen(title)];
	titleCop(button->title, title);
	button->width = strlen(title) + 8;
	button->height = 3;
	button->timer = std::chrono::high_resolution_clock::now();
	button->BUTTON_MAP = new WCHAR * [button->height];
	for (int i = 0; i < button->height; i++)
	{
		button->BUTTON_MAP[i] = new WCHAR[button->width];
		for (int j = 0; j < button->width; j++) button->BUTTON_MAP[i][j] = ' ';
	}
	
	button->BUTTON_MAP[0][0] = (WCHAR)9556;
	button->BUTTON_MAP[0][button->width - 1] = (WCHAR)9559;
	button->BUTTON_MAP[button->height - 1][0] = (WCHAR)9562;
	button->BUTTON_MAP[button->height - 1][button->width - 1] = (WCHAR)9565;
	for (int i = 0; i < button->width - 2; i++)
	{
		button->BUTTON_MAP[0][i + 1] = (WCHAR)9552;
		button->BUTTON_MAP[button->height - 1][i + 1] = (WCHAR)9552;
	}
	for (int i = 0; i < button->width - 8; i++) button->BUTTON_MAP[1][i + 4] = button->title[i];
}

void setPosition(Button* button, int _x, int _y)
{
	button->x = _x;
	button->y = _y;
}

void titleCop(char* title, const char* arr)
{
	for (int i = 0; i < strlen(arr); i++)
		title[i] = arr[i];
}