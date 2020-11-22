#include "GameDrawing.h"

void drawPanels(ControlPanel* game)
{
    // int k = 0;
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
            game->gameMap[i][0].Char.UnicodeChar = LEFT_TOP_ANGLE;
            game->gameMap[i][GAME_WIDTH - 1].Char.UnicodeChar = RIGHT_TOP_ANGLE;
        }
        else if (i == GAME_HEIGHT - 1)
        {
            game->gameMap[i][0].Char.UnicodeChar = LEFT_BOTTOM_ANGLE;
            game->gameMap[i][GAME_WIDTH - 1].Char.UnicodeChar = RIGHT_BOTTOM_ANGLE;
        }
        else
        {
            game->gameMap[i][0].Char.UnicodeChar = VERTICAL_LINE;
            game->gameMap[i][GAME_WIDTH - 1].Char.UnicodeChar = VERTICAL_LINE;
        }
    }

    // horizontal lines
    for (int i = 0; i < GAME_WIDTH - 2; i++)
    {
        game->gameMap[0][i + 1].Char.UnicodeChar = HORIZONTAL_LINE;
        game->gameMap[GAME_HEIGHT - 1][i + 1].Char.UnicodeChar = HORIZONTAL_LINE;
    }

    switch (game->state)
    {
    case MENU:

        break;
    case GAME:
        for (int i = 0; i < GAME_WIDTH - 2; i++)
            game->gameMap[GAME_HEIGHT - 3][i + 1].Char.UnicodeChar = HORIZONTAL_LINE;
        game->gameMap[GAME_HEIGHT - 3][0].Char.UnicodeChar = VERTICAL_TO_RIGHT;
        game->gameMap[GAME_HEIGHT - 3][GAME_WIDTH - 1].Char.UnicodeChar = VERTICAL_TO_LEFT;
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
    for (int i = 0; i < strlen(text); i++) game->gameMap[_y][_x + i].Char.UnicodeChar = text[i];
}

void drawInt(ControlPanel* game, int num, int _x, int _y)
{
    if (num == 0)
        game->gameMap[_y][_x].Char.UnicodeChar = 48;
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
        for (int j = 0; j < i; j++) game->gameMap[_y][_x + j].Char.UnicodeChar = arr[j];
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

void draw(ControlPanel* game, Button* button, bool type)
{
    if (type == 1)
    {
        for (int i = 0; i < button->height; i++)
        {
            for (int j = 0; j < button->width; j++)
            {
                game->gameMap[button->y + i][button->x + j].Char.UnicodeChar = button->BUTTON_MAP[i][j];
                if (button->isActive)
                    if (i == 1 && (j > 0 && j < button->width - 1))
                        game->gameMap[button->y + i][button->x + j].Attributes = button->uniqueColor;
                    else game->gameMap[button->y + i][button->x + j].Attributes = game->gameColor;
                else game->gameMap[button->y + i][button->x + j].Attributes = game->gameColor;
            }
        }
    }
    else
    {
        for (int i = 0; i < button->height; i++)
        {
            for (int j = 0; j < button->width; j++)
            {
                game->gameMap[button->y + i][button->x + j].Char.UnicodeChar = button->BUTTON_EMPTY_MAP[i][j];
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

void drawLogo(ControlPanel* game, int _x, int _y) {
    WCHAR logo[18][29]{
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ', ' ', ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ', ' ', ' ',                ' ',                ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ', ' ', ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ', ' ', ' ',                ' ',                ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', ' ', ' ', ' ', ' ' },
    { (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', ' ', ' ', ' ', ' ' },
    {                ' ',                ' ',                ' ',                ' ',                ' ',                ' ', ' ', ' ',                ' ',                ' ', ' ', ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ', ' ', ' ',                ' ',                ' ' },
    {                ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ' },
    {                ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ', (WCHAR)LOGO_TEXTURE },
    {                ' ',                ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ' },
    {                ' ',                ' ',                ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE,                ' ',                ' ', ' ', (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, (WCHAR)LOGO_TEXTURE, ' ', ' ', (WCHAR)LOGO_TEXTURE,                ' ', (WCHAR)LOGO_TEXTURE,                ' ' },
    {                ' ',                ' ',                ' ',                ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ', ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ',                ' ',                ' ',                ' ', (WCHAR)LOGO_TEXTURE, ' ', ' ', (WCHAR)LOGO_TEXTURE,                ' ',                ' ', (WCHAR)LOGO_TEXTURE }
    };
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 29; j++)
        {
            if (logo[i][j] != ' ')
            {
                game->gameMap[_y + i][_x + j].Char.UnicodeChar = logo[i][j];
                game->gameMap[_y + i][_x + j].Attributes = game->gameColor;
            }
        }
    }
}