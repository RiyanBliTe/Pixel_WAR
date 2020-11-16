#ifndef BUTTON_H
#define BUTTON_H

#include <Windows.h>
#include <chrono>

struct Button
{
	int x;
	int y;

	int width;
	int height;

	char* title;

	std::chrono::steady_clock::time_point timer;

	WCHAR** BUTTON_MAP;
};

void initButton(Button* button, const char* title);
void setPosition(Button* button, int _x, int _y);
void titleCop(char* title, const char* arr);

#endif // !BUTTON_H
