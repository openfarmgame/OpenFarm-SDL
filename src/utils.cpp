#include <vector>
#include <iostream>
#include <array>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils.h"

SDL_Texture *LoadImage(SDL_Renderer *renderer, const char *path) {
    SDL_Texture *grass_image = IMG_LoadTexture(renderer, path);
    if (grass_image == nullptr) {
        std::cerr << "IMG_LoadTexture error: " << IMG_GetError() << "\n";
        return nullptr;
    }
    return grass_image;
}

void SetColor(SDL_Renderer* renderer, SDL_Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

PerVector2 GetSize(SDL_Texture *texture) {
    PerVector2 size;
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    return size;
}

constexpr int FONT_WIDTH = 8;
constexpr int FONT_HEIGHT = 16;
constexpr int FONTMAP_SIZE = 160;
constexpr int GRID_COLUMNS = 10; // 한 줄 글자 수


std::array<int, 2> IndexToXY(int index) {
    int x = (index - 32) % GRID_COLUMNS;
    int y = (index - 32) / GRID_COLUMNS;
    return {x, y};
}

void RenderText(SDL_Renderer *renderer, SDL_Texture *fontTexture, 
                 const char *text, int x, int y, int size, 
                 int space_x, int space_y, SDL_Color color)
{
    SDL_SetTextureColorMod(fontTexture, color.r, color.g, color.b);
    //SDL_SetTextureAlphaMod(fontTexture, color.a);

    int len = strlen(text);
    int cursor_x = x;
    int cursor_y = y;
    int line_height = FONT_HEIGHT * size + space_y;

    for (int i = 0; i < len; i++)
    {
        char c = text[i];

        if (c == '\n')
        {
            cursor_x = x;
            cursor_y += line_height;
            continue;
        }
        std::array<int, 2> xy = IndexToXY(c);

        SDL_Rect srcRect = { 
            xy[0] * FONT_HEIGHT, 
            xy[1] * FONT_HEIGHT, 
            FONT_HEIGHT, 
            FONT_HEIGHT
        };

        SDL_Rect destRect = { 
            cursor_x, 
            cursor_y, 
            16 * size, 
            16 * size 
        };

        SDL_RenderCopy(renderer, fontTexture, &srcRect, &destRect);

        cursor_x += FONT_WIDTH * size + space_x; // 실질적으로 가로 8에 세로 16짜리 폰트임
    }
}