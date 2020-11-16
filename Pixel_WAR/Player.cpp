#include "Player.h"
#include "ControlPanel.h"

void initPlayer(Player* player)
{
	player->speed = 1;
	player->lives = 5;
	player->width = 5;
	player->height = 4;
	player->score = 0;
	player->weapon = 1;
	player->uniqueColor = 0x95;
	player->up = false;
	player->down = false;
	player->left = false;
	player->right = false;
	player->dead = false;
	player->hit = false;
	player->hitTimer = std::chrono::high_resolution_clock::now();
	player->PLAYER_MAP = new WCHAR* [player->height]{
		new WCHAR[player->width] { ' ',			   ' ', (WCHAR)9608,		 ' ',		' ' },
		new WCHAR[player->width] { ' ',       (WCHAR)9616, (WCHAR)9608, (WCHAR)9612,		' ' },
		new WCHAR[player->width] { (WCHAR)9616, (WCHAR)9608, (WCHAR)9600, (WCHAR)9608, (WCHAR)9612 },
		new WCHAR[player->width] { ' ',       (WCHAR)9600,		  ' ', (WCHAR)9600,		' ' }
	};
	player->PLAYER_EMPTY_MAP = new char* [player->height]{
		new char[player->width] {' ', ' ', ' ', ' ', ' '},
		new char[player->width] {' ', ' ', ' ', ' ', ' '},
		new char[player->width] {' ', ' ', ' ', ' ', ' '},
		new char[player->width] {' ', ' ', ' ', ' ', ' '}
	};
	player->PLAYER_COLOR_MAP = new WORD * [player->height]{
		new WORD[player->width] { 0, 0, 0x9A, 0, 0 },
		new WORD[player->width] { 0, 0x9A, player->uniqueColor, 0x9A, 0 },
		new WORD[player->width] { 0x9A, player->uniqueColor, player->uniqueColor, player->uniqueColor, 0x9A },
		new WORD[player->width] { 0, 0x9A, 0, 0x9A, 0 },
	};
}

void setPlayerLocation(Player* player, int _x, int _y)
{
	player->x = _x;
	player->y = _y;
}

void updatePlayer(Player* player)
{
	int dx = 0, dy = 0;
	if (player->up == true && player->y > 1)
	{
		dy -= player->speed;
	}
	if (player->down == true && player->y < GAME_HEIGHT - player->height - 3)
	{
		dy += player->speed;
	}
	if (player->left == true && player->x > 1 && player->x - player->speed * 2 > 0)
	{
		dx -= player->speed * 2;
	}
	else if (player->left == true && player->x > 1 && player->x - player->speed * 2 == 0)
	{
		dx -= player->speed;
	}
	if (player->right == true && player->x < GAME_WIDTH - player->width - 1 && (player->x + player->speed * 2) < GAME_WIDTH - 1 - player->width)
	{
		dx += player->speed * 2;
	}
	else if (player->right == true && player->x < GAME_WIDTH - player->width - 1 && (player->x + player->speed * 2) == GAME_WIDTH - 1 - player->width)
	{
		dx += player->speed;
	}

	player->y += dy;
	player->x += dx;

	dx = 0;
	dy = 0;
}

void hit(Player* player)
{
	player->lives--;
	if (player->lives <= 0)
	{
		player->dead = true;
	}
	player->hit = true;
	player->hitTimer = std::chrono::high_resolution_clock::now();
}

bool inPlayer(Player* player, int _x, int _y)
{
	for (int i = player->height - 1; i >= 0; i--)
		for (int j = 0; j < player->width; j++)
			if (player->PLAYER_MAP[i][j] != ' ')
				if (player->y + i == _y && player->x + j == _x) return true;
	return false;
}