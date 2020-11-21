#include "ControlPanel.h"

#include <math.h>
#include "GameDrawing.h"
#include <iostream>

void initPanel(ControlPanel* game)
{
    game->mainLoop = true;
    game->menuLoop = false;
    game->gameLoop = false;
    game->playerRedraw = true;
    game->gamePressed = false;
    game->state = MENU;
    game->timer = std::chrono::high_resolution_clock::now();
    game->firingTimer = std::chrono::high_resolution_clock::now();
    game->gameColor = 0x9F;
    game->hitColor = 0x9E;
    game->firingDelay = 300;
    game->gameCount = 0;

    initPlayer(&game->player);
    setPlayerLocation(&game->player, GAME_WIDTH / 2 - game->player.width / 2, GAME_HEIGHT - game->player.height - 10);

    initBulletsVector(&game->bullets);
    initEnemiesVector(&game->enemies);
    initPWUVector(&game->powerUps);
    initButtonContainer(&game->buttons);
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

    for (int i = 0; i < GAME_HEIGHT; i++)
        for (int j = 0; j < GAME_WIDTH; j++)
        {
            game->gameMap[i][j].Char.UnicodeChar = ' ';
            game->gameMap[i][j].Attributes = game->gameColor;
        }

    std::chrono::high_resolution_clock::time_point now;
    long elapsed = 0;

    Button b1;
    initButton(&b1, "Play Game");
    addButton(&game->buttons, b1);
    initButton(&b1, "Exit");
    addButton(&game->buttons, b1);
    setPosButtonContainer(&game->buttons, GAME_WIDTH / 2 - game->buttons.width / 2, GAME_HEIGHT / 2 + GAME_HEIGHT / 4 - game->buttons.height / 2);

    Enemy enemy;

    int enemyCount = 4;

    while (game->mainLoop)
    {
        drawPanels(game);
        switch (game->state)
        {
        case MENU:

            drawLogo(game, GAME_WIDTH / 2 - 29 / 2 - 1, GAME_HEIGHT / 4 - 18 / 2 + 5);
            game->gameLoop = false;
            game->menuLoop = true;
            while (game->menuLoop)
            {
                now = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - game->timer).count() / 1000000;
                if (elapsed > 45)
                {
                    checkKeys(game);
                    gameRender(game);
                    WriteConsoleOutput(hOutput, (CHAR_INFO*)game->gameMap, dwBufferSize, dwBufferCoord, &rcRegion);
                    gameUpdate(game);
                    game->timer = std::chrono::high_resolution_clock::now();
                }
            }

            break;
        case GAME:

            game->menuLoop = false;
            game->gameLoop = true;
            while (game->gameLoop)
            {
                now = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - game->timer).count() / 1000000;
                if (elapsed > 45)
                {
                    if (game->enemies.size == 0)
                    {
                        for (int i = 0; i < enemyCount; i++)
                        {
                            initEnemy(&enemy, rand() % 4);
                            push_backEnemy(&game->enemies, enemy);
                        }
                        enemyCount++;
                    }
                    checkKeys(game);
                    gameRender(game);
                    WriteConsoleOutput(hOutput, (CHAR_INFO*)game->gameMap, dwBufferSize, dwBufferCoord, &rcRegion);
                    gameUpdate(game);
                    game->timer = std::chrono::high_resolution_clock::now();
                }
            }

            break;
        default:
            break;
        }
    }
    deleteVector(&game->bullets);
    deleteBContainer(&game->buttons);
}

void consoleSettings()
{
    HWND hWnd = GetConsoleWindow();
    MoveWindow(hWnd, 25, 25, GAME_WIDTH * 8 + 35, GAME_HEIGHT * 16 + 40, TRUE);
}

void checkKeys(ControlPanel* game)
{
    if (game->state == MENU)
    {
        //key pressed
        if (GetAsyncKeyState(VK_DOWN) < 0 && GetAsyncKeyState(VK_UP) == 0) {
            if (!game->buttons.pressed)
            {
                game->buttons.buttons[game->buttons.activePosition].isActive = false;
                game->buttons.activePosition = (game->buttons.activePosition + 1) % game->buttons.size;
                game->buttons.buttons[game->buttons.activePosition].isActive = true;
                game->buttons.pressed = true;
            }
        } // key released
        else if (GetAsyncKeyState(VK_DOWN) == 0 && GetAsyncKeyState(VK_UP) == 0) { game->buttons.pressed = false; }

        if (GetAsyncKeyState(VK_UP) < 0 && GetAsyncKeyState(VK_DOWN) == 0) {
            if (!game->buttons.pressed)
            {
                game->buttons.buttons[game->buttons.activePosition].isActive = false;
                game->buttons.activePosition = abs(game->buttons.activePosition - 1) % game->buttons.size;
                game->buttons.buttons[game->buttons.activePosition].isActive = true;
                game->buttons.pressed = true;
            }
        }
        else if (GetAsyncKeyState(VK_UP) == 0 && GetAsyncKeyState(VK_DOWN) == 0) { game->buttons.pressed = false; }

        // enter key
        if (GetAsyncKeyState(VK_RETURN) < 0) {
            if (strcmp(game->buttons.buttons[game->buttons.activePosition].title, "Play Game") == 0) { game->menuLoop = false; game->gameLoop = true; game->state = GAME; }
            else if (strcmp(game->buttons.buttons[game->buttons.activePosition].title, "Exit") == 0) { game->gameLoop = false; game->menuLoop = false; game->mainLoop = false; }
        }

        if (GetAsyncKeyState(VK_ESCAPE) < 0) {
            if (!game->gamePressed)
            {
                game->gameLoop = false;
                game->menuLoop = false;
                game->mainLoop = false;
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE) == 0 && game->gamePressed) game->gamePressed = false;
    }
    else if (game->state == GAME)
    {
        // key pressed
        if (GetAsyncKeyState(VK_UP) < 0) { game->player.up = true; game->playerRedraw = true; }
        if (GetAsyncKeyState(VK_DOWN) < 0) { game->player.down = true; game->playerRedraw = true; }
        if (GetAsyncKeyState(VK_RIGHT) < 0) { game->player.right = true; game->playerRedraw = true; }
        if (GetAsyncKeyState(VK_LEFT) < 0) { game->player.left = true; game->playerRedraw = true; }
        if (GetAsyncKeyState(VK_SPACE) < 0) { game->player.firing = true; }
        if (GetAsyncKeyState(VK_ESCAPE) < 0) { game->gameLoop = false; game->menuLoop = true; game->state = MENU; game->gamePressed = true; }

        //key released
        if (GetAsyncKeyState(VK_UP) == 0) { game->player.up = false; }
        if (GetAsyncKeyState(VK_DOWN) == 0) { game->player.down = false; }
        if (GetAsyncKeyState(VK_RIGHT) == 0) { game->player.right = false; }
        if (GetAsyncKeyState(VK_LEFT) == 0) { game->player.left = false; }
        if (GetAsyncKeyState(VK_SPACE) == 0) { game->player.firing = false; }
    }
}

void gameUpdate(ControlPanel* game)
{
    if (game->state == MENU)
    {
        // buttons
        for (int i = 0; i < game->buttons.size; i++)
        {
            draw(game, &game->buttons.buttons[i], 0);
        }
    }
    else if (game->state == GAME)
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
                eraseBullet(&game->bullets, i--);
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
                    switch (game->bullets.bullets[i].type) {
                    case 1:
                        hit(&game->enemies.enemies[i], 1);
                        break;
                    case 2:
                        hit(&game->enemies.enemies[i], 2);
                        break;
                    case 3:
                        hit(&game->enemies.enemies[i], 3);
                        break;
                    case 4:
                        hit(&game->enemies.enemies[i], 4);
                        break;
                    }
                    game->enemies.enemies[i].uniqueColor = 0x94;
                    draw(game, &game->bullets.bullets[j], 0);
                    eraseBullet(&game->bullets, j);

                    if (removeEnemy(&game->enemies.enemies[i]))
                    {
                        switch (game->enemies.enemies[i].type)
                        {
                        case 1: game->player.score += 1; break;
                        case 2: game->player.score += 2; break;
                        case 3:	game->player.score += 4; break;
                        case 4:	game->player.score += 8; break;
                        default: break;
                        }
                        double chanse = rand() * 1.0 / RAND_MAX;
                        if (chanse < 0.15)
                        {
                            PowerUp pwu;
                            initPowerUp(&pwu, HEALTH);
                            setPowerUpLocation(&pwu, game->enemies.enemies[i].x + game->enemies.enemies[i].width / 2, game->enemies.enemies[i].y + game->enemies.enemies->height / 2);
                            push_backPowerUp(&game->powerUps, pwu);
                        }
                        else if (chanse < 0.25)
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
                    hit(&game->enemies.enemies[i], 1);
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
                        eraseEnemy(&game->enemies, i--);
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
}

void gameRender(ControlPanel* game)
{
    if (game->state == MENU)
    {
        // buttons
        for (int i = 0; i < game->buttons.size; i++)
        {
            draw(game, &game->buttons.buttons[i], 1);
        }
    }
    else if (game->state == GAME)
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
}