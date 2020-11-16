#include "ControlPanel.h"

#include <iostream>

void initPanel(ControlPanel* game)
{
	game->mainLoop =	 true;
	game->menuLoop =	 false;
	game->gameLoop =	 false;
	game->playerRedraw = true;
	game->state =		 game->GAME;
	game->timer =		 std::chrono::high_resolution_clock::now();
	game->timer =		 std::chrono::high_resolution_clock::now();
	game->gameColor =	 0x9F;
	game->hitColor =	 0x9E;
	game->firingDelay =  300;

	initPlayer(&game->player);
	setPlayerLocation(&game->player, GAME_WIDTH / 2 - game->player.width / 2, GAME_HEIGHT - game->player.height - 10);
	initBulletsVector(&game->bullets);
	initEnemiesVector(&game->enemies);
	initPWUVector(&game->powerUps);
}

void showGame(ControlPanel* game)
{
	consoleSettings();
	initPanel(game);

	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferSize = { GAME_WIDTH, GAME_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, GAME_WIDTH - 1, GAME_HEIGHT - 1 };
		
	ReadConsoleOutput(hOutput, (CHAR_INFO*)game->gameMap, dwBufferSize,
		dwBufferCoord, &rcRegion);

	Button button;
	initButton(&button, "New Game");
	setPosition(&button, 10, 12);
	draw(game, &button);

	std::chrono::steady_clock::time_point now;
	long elapsed = 0;

	for (int i = 0; i < 25; i++)
	{
		Enemy enemy;
		initEnemy(&enemy, 1);
		push_backEnemy(&game->enemies, enemy);
	}
	

	while (game->mainLoop)
	{
		switch (game->state)
		{
		case game->MENU:

			drawPanels(game);

			game->menuLoop = true;
			while (game->menuLoop)
			{
				now = std::chrono::high_resolution_clock::now();
				elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - game->timer).count() / 1000000;
				if (elapsed > 45)
				{
					now = std::chrono::high_resolution_clock::now();
					elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - button.timer).count() / 1000000;
					
					if (elapsed > 850)
					{
						button.x++;
						draw(game, &button);
						button.timer = std::chrono::high_resolution_clock::now();
						WriteConsoleOutput(hOutput, (CHAR_INFO*)game->gameMap, dwBufferSize,
							dwBufferCoord, &rcRegion);
					}
					game->timer = std::chrono::high_resolution_clock::now();
				}
			}

			break;
		case game->GAME:

			drawPanels(game);

			game->gameLoop = true;
			while (game->gameLoop)
			{
			now = std::chrono::high_resolution_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - game->timer).count() / 1000000;
				if (elapsed > 50)
				{
					checkKeys(game);
					gameRender(game);
					WriteConsoleOutput(hOutput, (CHAR_INFO*)game->gameMap, dwBufferSize,
						dwBufferCoord, &rcRegion);
					gameUpdate(game);
					game->timer = std::chrono::high_resolution_clock::now();
				}
			}

			break;
		default:
			break;
		}
	}
}

void gameUpdate(ControlPanel* game)
{
	if (game->player.firing)
	{
		auto now = std::chrono::high_resolution_clock::now();
		long elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - game->firingTimer).count() / 1000000;
		if (elapsed > game->firingDelay)
		{
			Bullet bullet;
			switch (game->player.weapon)
			{
			case 1:
				initBullet(&bullet, 1);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2, game->player.y);
				push_backBullet(&game->bullets, bullet);
				break;
			case 2:
				initBullet(&bullet, 1);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 - 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				initBullet(&bullet, 1);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 + 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				break;
			case 3:
				initBullet(&bullet, 2);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 - 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				initBullet(&bullet, 2);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 + 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				break;
			case 4:
				initBullet(&bullet, 3);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 - 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				initBullet(&bullet, 3);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 + 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				break;
			case 5:
				initBullet(&bullet, 4);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 - 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				initBullet(&bullet, 4);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 + 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
			case 6:
				initBullet(&bullet, 5);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 - 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				initBullet(&bullet, 5);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2 + 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				break;
			case 7:
				initBullet(&bullet, 5);
				setBulletLocation(&bullet, game->player.x, game->player.y);
				push_backBullet(&game->bullets, bullet);
				initBullet(&bullet, 5);
				setBulletLocation(&bullet, game->player.x + game->player.width / 2, game->player.y);
				push_backBullet(&game->bullets, bullet);
				initBullet(&bullet, 5);
				setBulletLocation(&bullet, game->player.x + game->player.width - 1, game->player.y);
				push_backBullet(&game->bullets, bullet);
				break;
			default:
				break;
			}

			game->firingTimer = std::chrono::high_resolution_clock::now();
		}
	}

	for (int i = 0; i < game->bullets.size; i++)
	{
		if (removeBullet(&game->bullets.bullets[i]))
		{
			draw(game, &game->bullets.bullets[i], 0);
			eraseBullet(&game->bullets, i);
			i--;
		}
		else
		{
			draw(game, &game->bullets.bullets[i], 0);
			updateBullet(&game->bullets.bullets[i]);
		}
	}

	for (int i = 0; i < game->enemies.size; i++)
	{
		for (int j = 0; j < game->bullets.size; j++)
		{
			if (inEnemy(&game->enemies.enemies[i], game->bullets.bullets[j].x, game->bullets.bullets[j].y))
			{
				hit(&game->enemies.enemies[i]);
				game->enemies.enemies[i].uniqueColor = 0x94;
				draw(game, &game->bullets.bullets[j], 0);
				eraseBullet(&game->bullets, j);

				if (removeEnemy(&game->enemies.enemies[i]))
				{
					switch (game->enemies.enemies[i].type)
					{
					case 1:
						game->player.score += 1;
						break;
					case 2:
						game->player.score += 2;
						break;
					case 3:
						game->player.score += 4;
						break;
					case 4:
						game->player.score += 8;
						break;
					default:
						break;
					}
					//srand(time(NULL));
					double chanse = rand() * 1.0 / RAND_MAX;
					//std::cout << chanse << std::endl;
					if (chanse < 0.10)
					{
						PowerUp pwu;
						initPowerUp(&pwu, HEALTH);
						setPowerUpLocation(&pwu, game->enemies.enemies[i].x + game->enemies.enemies[i].width / 2, game->enemies.enemies[i].y + game->enemies.enemies->height / 2);
						push_backPowerUp(&game->powerUps, pwu);
					}
					else if (chanse < 0.15)
					{
						PowerUp pwu;
						initPowerUp(&pwu, WEAPON);
						setPowerUpLocation(&pwu, game->enemies.enemies[i].x + game->enemies.enemies[i].width / 2, game->enemies.enemies[i].y + game->enemies.enemies->height / 2);
						push_backPowerUp(&game->powerUps, pwu);
					}
					draw(game, &game->enemies.enemies[i], 0);
					eraseEnemy(&game->enemies, i);
				}				
			}
		}
	}

	for (int i = 0; i < game->enemies.size; i++)
	{
		if (!game->player.hit)
			if (inEnemy(&game->enemies.enemies[i], &game->player))
			{
				hit(&game->player);
				game->player.uniqueColor = 0x94;
				hit(&game->enemies.enemies[i]);
				game->enemies.enemies[i].uniqueColor = 0x94;
				if (removeEnemy(&game->enemies.enemies[i]))
				{
					switch (game->enemies.enemies[i].type)
					{
					case 1:
						game->player.score += 1;
						break;
					case 2:
						game->player.score += 2;
						break;
					case 3:
						game->player.score += 4;
						break;
					case 4:
						game->player.score += 8;
						break;
					default:
						break;
					}
					draw(game, &game->enemies.enemies[i], 0);
					eraseEnemy(&game->enemies, i);
				}
			}
	}

	for (int i = 0; i < game->powerUps.size; i++)
	{
		if (inPlayer(&game->player, game->powerUps.pwus[i].x, game->powerUps.pwus[i].y))
		{
			if (game->powerUps.pwus[i].type == HEALTH) game->player.lives++;
			else if (game->powerUps.pwus[i].type == WEAPON && game->player.weapon < 7) game->player.weapon++;
			draw(game, &game->powerUps.pwus[i], 0);
			erasePowerUp(&game->powerUps, i);
		}
		else if (removePowerUp(&game->powerUps.pwus[i]))
		{
			draw(game, &game->powerUps.pwus[i], 0);
			erasePowerUp(&game->powerUps, i);
		}
		else
		{
			draw(game, &game->powerUps.pwus[i], 0);
			updatePowerUp(&game->powerUps.pwus[i]);
		}
	}

	for (int i = 0; i < game->enemies.size; i++)
	{
			draw(game, &game->enemies.enemies[i], 0);
			updateEnemy(&game->enemies.enemies[i]);
	}

	draw(game, &game->player, 0);
	updatePlayer(&game->player);
}

void gameRender(ControlPanel* game)
{
	for (int i = 0; i < game->bullets.size; i++)
		draw(game, &game->bullets.bullets[i], 1);
	
	for (int i = 0; i < game->enemies.size; i++)
		draw(game, &game->enemies.enemies[i], 1);

	for (int i = 0; i < game->powerUps.size; i++)
		draw(game, &game->powerUps.pwus[i], 1);

	drawInt(game, game->player.score, GAME_WIDTH - 6, GAME_HEIGHT - 2);
	drawInt(game, game->player.weapon, 20, GAME_HEIGHT - 2);
	drawInt(game, game->player.lives, 9, GAME_HEIGHT - 2);
	
	draw(game, &game->player, 1);
}

void consoleSettings()
{
	HWND hWnd = GetConsoleWindow();
	MoveWindow(hWnd, 0, 0, GAME_WIDTH * 8 + 35, GAME_HEIGHT * 16 + 40, TRUE);
}

void checkKeys(ControlPanel* game)
{
	// key pressed
	if (GetAsyncKeyState(VK_UP) < 0) { game->player.up = true; game->playerRedraw = true; }
	if (GetAsyncKeyState(VK_DOWN) < 0) { game->player.down = true; game->playerRedraw = true; }
	if (GetAsyncKeyState(VK_RIGHT) < 0) { game->player.right = true; game->playerRedraw = true; }
	if (GetAsyncKeyState(VK_LEFT) < 0) { game->player.left = true; game->playerRedraw = true; }
	if (GetAsyncKeyState(VK_SPACE) < 0) { game->player.firing = true; }
	//if (GetAsyncKeyState(VK_ESCAPE) < 0) { game->gameRun = false; running = false; }

	//key released
	if (GetAsyncKeyState(VK_UP) == 0) { game->player.up = false; }
	if (GetAsyncKeyState(VK_DOWN) == 0) { game->player.down = false; }
	if (GetAsyncKeyState(VK_RIGHT) == 0) { game->player.right = false; }
	if (GetAsyncKeyState(VK_LEFT) == 0) { game->player.left = false; }
	if (GetAsyncKeyState(VK_SPACE) == 0) { game->player.firing = false; }
}

void drawPanels(ControlPanel* game)
{
	//int k = 0;
	for (int i = 0; i < GAME_HEIGHT; i++)
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			game->gameMap[i][j].Char.UnicodeChar = ' ';
			//game->gameMap[i][j].Char.UnicodeChar = (WCHAR)k++;
			game->gameMap[i][j].Attributes = game->gameColor;
		}

	// vertical lines
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		if (i == 0)
		{
			game->gameMap[i][0].Char.UnicodeChar = (WCHAR)9556;
			game->gameMap[i][GAME_WIDTH - 1].Char.UnicodeChar = (WCHAR)9559;
		}
		else if (i == GAME_HEIGHT - 1)
		{
			game->gameMap[i][0].Char.UnicodeChar = (WCHAR)9562;
			game->gameMap[i][GAME_WIDTH - 1].Char.UnicodeChar = (WCHAR)9565;
		}
		else
		{
			game->gameMap[i][0].Char.UnicodeChar = (WCHAR)9553;
			game->gameMap[i][GAME_WIDTH - 1].Char.UnicodeChar = (WCHAR)9553;
		}
	}

	// horizontal lines
	for (int i = 0; i < GAME_WIDTH - 2; i++)
	{
		game->gameMap[0][i + 1].Char.UnicodeChar = (WCHAR)9552;
		game->gameMap[GAME_HEIGHT - 1][i + 1].Char.UnicodeChar = (WCHAR)9552;
	}

	switch (game->state)
	{
	case game->MENU:
		
		break;
	case game->GAME:
		for (int i = 0; i < GAME_WIDTH - 2; i++)
			game->gameMap[GAME_HEIGHT - 3][i + 1].Char.UnicodeChar = (WCHAR)9552;
		game->gameMap[GAME_HEIGHT - 3][0].Char.UnicodeChar = (WCHAR)9568;
		game->gameMap[GAME_HEIGHT - 3][GAME_WIDTH - 1].Char.UnicodeChar = (WCHAR)9571;
		drawText(game, "Lives:", 2, GAME_HEIGHT - 2);
		drawText(game, "Weapon:", 12, GAME_HEIGHT - 2);
		drawText(game, "Score:", GAME_WIDTH - 13, GAME_HEIGHT - 2);
		break;
	default:
		break;
	}
}

void drawText(ControlPanel* game, const char* text, int _x, int _y)
{
	for (int i = 0; i < strlen(text); i++) game->gameMap[_y][_x + i].Char.UnicodeChar = (WCHAR)text[i];
}

void drawInt(ControlPanel* game, int num, int _x, int _y)
{
	if (num == 0)
		game->gameMap[_y][_x].Char.UnicodeChar = (WCHAR)48;
	else
	{
		int i = 0;
		char arr[50];
		while (num != 0)
		{
			arr[i++] = (char)(48 + num % 10);
			num /= 10;
		}
		for (int j = 0; j < i / 2; j++)
		{
			char a = arr[j];
			arr[j] = arr[i - j - 1];
			arr[i - j - 1] = a;
		}
		for (int j = 0; j < i; j++) game->gameMap[_y][_x + j].Char.UnicodeChar = (WCHAR)arr[j];
	}
}

void draw(ControlPanel* game, Player* player, bool type)
{
	if (type == 1)
	{
		for (int i = 0; i < player->height; i++)
			for (int j = 0; j < player->width; j++)
			{
				if (player->hit)
				{
					game->gameMap[player->y + i][player->x + j].Char.UnicodeChar = player->PLAYER_MAP[i][j];
					if (player->PLAYER_COLOR_MAP[i][j] != 0 && player->PLAYER_COLOR_MAP[i][j] != 0x9A) game->gameMap[player->y + i][player->x + j].Attributes = player->uniqueColor;
				}
				else if (player->PLAYER_MAP[i][j] != ' ')
				{
					game->gameMap[player->y + i][player->x + j].Char.UnicodeChar = player->PLAYER_MAP[i][j];
					if (player->PLAYER_COLOR_MAP[i][j] != 0) game->gameMap[player->y + i][player->x + j].Attributes = player->PLAYER_COLOR_MAP[i][j];
				}
			}
		if (player->hit)
		{
			auto now = std::chrono::high_resolution_clock::now();
			long elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - player->hitTimer).count() / 1000000;
			if (elapsed > 500)
			{
				player->uniqueColor = 0x95;
				player->hit = false;
			}
		}
	}
	else
	{
		for (int i = 0; i < player->height; i++)
			for (int j = 0; j < player->width; j++)
			{
				if (player->PLAYER_MAP[i][j] != ' ')
				{
					game->gameMap[player->y + i][player->x + j].Char.UnicodeChar = player->PLAYER_EMPTY_MAP[i][j];
					game->gameMap[player->y + i][player->x + j].Attributes = game->gameColor;
				}
			}
	}
}


void draw(ControlPanel* game, Bullet* bullet, bool type)
{
	if (type == 1)
	{
		game->gameMap[bullet->y][bullet->x].Char.UnicodeChar = bullet->BULLET;
		game->gameMap[bullet->y][bullet->x].Attributes = bullet->uniqueColor;
	}
	else
	{
		game->gameMap[bullet->y][bullet->x].Char.UnicodeChar = bullet->EMPTY_BULLET;
		game->gameMap[bullet->y][bullet->x].Attributes = game->gameColor;
	}
}

void draw(ControlPanel* game, Enemy* enemy, bool type)
{
	if (type == 1)
	{
		for (int i = 0; i < enemy->height; i++)
			for (int j = 0; j < enemy->width; j++)
			{
				if (enemy->hit)
				{
					game->gameMap[enemy->y + i][enemy->x + j].Char.UnicodeChar = enemy->ENEMY_MAP[i][j];
					if (enemy->COLOR_MAP[i][j] != 0) game->gameMap[enemy->y + i][enemy->x + j].Attributes = enemy->uniqueColor;
				}
				else if (enemy->ENEMY_MAP[i][j] != ' ')
				{
					game->gameMap[enemy->y + i][enemy->x + j].Char.UnicodeChar = enemy->ENEMY_MAP[i][j];
					if (enemy->COLOR_MAP[i][j] != 0) game->gameMap[enemy->y + i][enemy->x + j].Attributes = enemy->COLOR_MAP[i][j];
				}
			}
		if (enemy->hit)
		{
			auto now = std::chrono::high_resolution_clock::now();
			long elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - enemy->timer).count() / 1000000;
			if (elapsed > 80)
			{
				switch (enemy->type)
				{
				case 1:
					enemy->uniqueColor = ENEMY_COLOR_1;
					break;
				case 2:
					enemy->uniqueColor = ENEMY_COLOR_2;
					break;
				case 3:
					enemy->uniqueColor = ENEMY_COLOR_3;
					break;
				case 4:
					enemy->uniqueColor = ENEMY_COLOR_4;
					break;
				default:
					break;
				}
				enemy->hit = false;
			}
		}
	}
	else
		for (int i = 0; i < enemy->height; i++)
			for (int j = 0; j < enemy->width; j++)
				if (enemy->ENEMY_MAP[i][j] != ' ')
				{
					game->gameMap[enemy->y + i][enemy->x + j].Char.UnicodeChar = enemy->ENEMY_EMPTY_MAP[i][j];
					game->gameMap[enemy->y + i][enemy->x + j].Attributes = game->gameColor;
				}
}

void draw(ControlPanel* game, Button* button)
{
	for (int i = 0; i < button->height; i++)
	{
		for (int j = 0; j < button->width; j++)
		{
			game->gameMap[button->y + i][button->x + j].Char.UnicodeChar = button->BUTTON_MAP[i][j];
		}
	}
}

void draw(ControlPanel* game, PowerUp* pwu, bool type)
{
	if (type == 1)
	{
		game->gameMap[pwu->y][pwu->x].Char.UnicodeChar = pwu->SYMBOL;
		game->gameMap[pwu->y][pwu->x].Attributes = pwu->color;
	}
	else
	{
		game->gameMap[pwu->y][pwu->x].Char.UnicodeChar = pwu->EMPTY_SYMBOL;
		game->gameMap[pwu->y][pwu->x].Attributes = game->gameColor;
	}
}