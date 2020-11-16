#include "Enemy.h"

#include <ctime>
#include <iostream>

#include "ControlPanel.h"

void nextDir(eDirection& dir, eDirection side)
{
	srand(time(NULL));
	int dodrand = rand() % 2;
	switch (side)
	{
	case TOP:
		switch (dir)
		{
		case TOP:
			if (dodrand == 1) dir = BOTTOM_RIGHT;
			else dir = BOTTOM_LEFT;
			break;
		case TOP_RIGHT:
			if (dodrand == 1) dir = BOTTOM;
			else dir = BOTTOM_RIGHT;
			break;
		case TOP_LEFT:
			if (dodrand == 1) dir = BOTTOM_LEFT;
			else dir = BOTTOM;
			break;
		default:
			break;
		}
		break;
	case RIGHT:
		switch (dir)
		{
		case RIGHT:
			if (dodrand == 1) dir = TOP_LEFT;
			else dir = BOTTOM_LEFT;
			break;
		case BOTTOM_RIGHT:
			if (dodrand == 1) dir = LEFT;
			else dir = BOTTOM_LEFT;
			break;
		case TOP_RIGHT:
			if (dodrand == 1) dir = LEFT;
			else dir = TOP_LEFT;
			break;
		default:
			break;
		}
		break;
	case BOTTOM:
		switch (dir)
		{
		case BOTTOM:
			if (dodrand == 1) dir = TOP_LEFT;
			else dir = TOP_RIGHT;
			break;
		case BOTTOM_RIGHT:
			if (dodrand == 1) dir = TOP;
			else dir = TOP_RIGHT;
			break;
		case BOTTOM_LEFT:
			if (dodrand == 1) dir = TOP_LEFT;
			else dir = TOP;
			break;
		default:
			break;
		}
		break;
	case LEFT:
		switch (dir)
		{
		case LEFT:
			if (dodrand == 1) dir = TOP_RIGHT;
			else dir = BOTTOM_RIGHT;
			break;
		case BOTTOM_LEFT:
			if (dodrand == 1) dir = RIGHT;
			else dir = BOTTOM_RIGHT;
			break;
		case TOP_LEFT:
			if (dodrand == 1) dir = RIGHT;
			else dir = TOP_RIGHT;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void initEnemy(Enemy* enemy, int type)
{
	enemy->speed = 1;
	enemy->width = 10;
	enemy->height = 5;
	int _x = GAME_WIDTH - enemy->width - 1;
	enemy->x = rand() % _x + 1;
	enemy->y = 1;
	enemy->dead = false;
	enemy->hit = false;
	enemy->timer = std::chrono::high_resolution_clock::now();
	enemy->type = type;
	switch (type)
	{
	case 1:
		enemy->uniqueColor = ENEMY_COLOR_1;
		enemy->health = 1;
		break;
	case 2:
		enemy->uniqueColor = ENEMY_COLOR_2;
		enemy->health = 15;
		break;
	case 3:
		enemy->uniqueColor = ENEMY_COLOR_3;
		enemy->health = 20;
		break;
	case 4:
		enemy->uniqueColor = ENEMY_COLOR_4;
		enemy->health = 30;
		break;
	default:
		break;
	}

	int newDir = rand() % 3 + 3;
	switch (newDir)
	{
	case BOTTOM_RIGHT:
		enemy->direction = BOTTOM_RIGHT;
		enemy->dx = enemy->speed;
		enemy->dy = enemy->speed;
		break;
	case BOTTOM:
		enemy->direction = BOTTOM;
		enemy->dx = 0;
		enemy->dy = enemy->speed;
		break;
	case BOTTOM_LEFT:
		enemy->direction = BOTTOM_LEFT;
		enemy->dx = -enemy->speed;
		enemy->dy = enemy->speed;
		break;
	default:
		break;
	}

	enemy->ENEMY_MAP = new WCHAR* [enemy->height]{
		new WCHAR[enemy->width] { ' ', ' ', ' ', (WCHAR)9604, (WCHAR)9608, (WCHAR)9608, (WCHAR)9604, ' ', ' ', ' ' },
		new WCHAR[enemy->width] { ' ', (WCHAR)9604, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9604, ' ' },
		new WCHAR[enemy->width] { (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608 },
		new WCHAR[enemy->width] { ' ', (WCHAR)9600, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9608, (WCHAR)9600, ' ' },
		new WCHAR[enemy->width] {  ' ', ' ', ' ', (WCHAR)9600, (WCHAR)9608, (WCHAR)9608, (WCHAR)9600, ' ', ' ', ' '  }
	};
	enemy->ENEMY_EMPTY_MAP = new WCHAR * [enemy->height]{
		new WCHAR[enemy->width] { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		new WCHAR[enemy->width] { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		new WCHAR[enemy->width] { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		new WCHAR[enemy->width] { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		new WCHAR[enemy->width] { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
	};
	enemy->COLOR_MAP = new WORD * [enemy->height]{
		new WORD[enemy->width] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		new WORD[enemy->width] { 0, 0, 0, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, 0, 0, 0 },
		new WORD[enemy->width] { 0, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, 0 },
		new WORD[enemy->width] { 0, 0, 0, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, enemy->uniqueColor, 0, 0, 0 },
		new WORD[enemy->width] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
}

void direction(Enemy* enemy)
{
	switch (enemy->direction)
	{
	case TOP:
		enemy->dx = 0;
		enemy->dy = -enemy->speed;
		break;
	case TOP_RIGHT:
		enemy->dx = enemy->speed;
		enemy->dy = -enemy->speed;
		break;
	case RIGHT:
		enemy->dx = enemy->speed * 2;
		enemy->dy = 0;
		break;
	case BOTTOM_RIGHT:
		enemy->dx = enemy->speed;
		enemy->dy = enemy->speed;
		break;
	case BOTTOM:
		enemy->dx = 0;
		enemy->dy = enemy->speed;
		break;
	case BOTTOM_LEFT:
		enemy->dx = -enemy->speed;
		enemy->dy = enemy->speed;
		break;
	case LEFT:
		enemy->dx = -enemy->speed * 2;
		enemy->dy = 0;
		break;
	case TOP_LEFT:
		enemy->dx = -enemy->speed;
		enemy->dy = -enemy->speed;
		break;
	default:
		break;
	}
}

void updateEnemy(Enemy* enemy)
{
	enemy->x += enemy->dx;
	enemy->y += enemy->dy;

	if (enemy->x <= 2) { nextDir(enemy->direction, LEFT); direction(enemy); }
	if (enemy->x >= GAME_WIDTH - enemy->width - 2) { nextDir(enemy->direction, RIGHT); direction(enemy); }
	if (enemy->y <= 1) { nextDir(enemy->direction, TOP); direction(enemy); }
	if (enemy->y >= GAME_HEIGHT - enemy->height - 3) { nextDir(enemy->direction, BOTTOM); direction(enemy); }
}

void hit(Enemy* enemy)
{
	enemy->health--;
	if (enemy->health <= 0)
	{
		enemy->dead = true;
	}
	enemy->hit = true;
	enemy->timer = std::chrono::high_resolution_clock::now();
}

bool inEnemy(Enemy* enemy, int _x, int _y)
{
	for (int i = 0; i < enemy->height; i++)
		for (int j = 0; j < enemy->width; j++)
			if (enemy->ENEMY_MAP[i][j] != ' ')
				if (enemy->y + i == _y && enemy->x + j == _x) return true;
	return false;
}

bool inEnemy(Enemy* enemy, Player* player)
{
	for (int i = 0; i < player->height; i++)
		for (int j = 0; j < player->width; j++)
			if (player->PLAYER_MAP[i][j] != ' ')
				if (inEnemy(enemy, j + player->x, i + player->y)) return true;
	return false;
}

bool inEnemy(Enemy* enemy1, Enemy* enemy2)
{
	for (int i = 0; i < enemy2->height; i++)
		for (int j = 0; j < enemy2->width; j++)
			if (enemy2->ENEMY_MAP[i][j] != ' ')
				if (inEnemy(enemy1, enemy2->x + j, enemy2->y + i))return true;
	return false;
}

bool removeEnemy(Enemy* enemy)
{
	return enemy->dead;
}