#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct SDL_Resources {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

template <size_t Width, size_t Height>
using MapData = std::array<std::array<int, Height>, Width>;

struct PerVector2 {
    int x, y;

    PerVector2 operator+(const PerVector2& other) const {
        return {x + other.x, y + other.y};
    }
};

struct PerFloatVector2 {
    float x, y;

    PerFloatVector2 operator+(const PerFloatVector2& other) const {
        return {x + other.x, y + other.y};
    }

    PerVector2 operator+(const PerVector2& other) const {
        return { static_cast<int>(x + other.x),
                 static_cast<int>(y + other.y) };
    }
};


SDL_Texture* LoadImage(SDL_Renderer *renderer, const char *path);
void SetColor(SDL_Renderer* renderer, SDL_Color c);
PerVector2 GetSize(SDL_Texture *texture);
void RenderText(SDL_Renderer *renderer, SDL_Texture *fontTexture, 
                 const char *text, int x, int y, int size, 
                 int space_x, int space_y, SDL_Color color);


constexpr int KEY_RIGHT = 1073741903;
constexpr int KEY_LEFT = 1073741904;
constexpr int KEY_DOWN = 1073741905;
constexpr int KEY_UP = 1073741906;

#endif