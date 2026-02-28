#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include <iostream>

class Player {
private:
    PerVector2 position;
    PerFloatVector2 velocity;
    SDL_Texture *texture;
    PerVector2 size;
    SDL_Rect dst;
    int speed = 100;

    bool keysDown[4] = {false, false, false, false};

public:
    Player(int x_pos, int y_pos, SDL_Texture* image, int size_x, int size_y) {
        position.x = x_pos;
        position.y = y_pos;
        texture = image;

        size = GetSize(texture);

        dst.w = size_x;
        dst.h = size_y;
    }

    Player(int x_pos, int y_pos, SDL_Texture* image) {
        position.x = x_pos;
        position.y = y_pos;
        texture = image;

        size = GetSize(texture);

        dst.w = size.x;
        dst.h = size.y;
    }


    void Draw(SDL_Renderer *renderer) {
        dst.x = position.x;
        dst.y = position.y;

        SDL_RenderCopy(renderer, texture, nullptr, &dst);
    }

    void Update(float deltaTime) {
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        velocity.x = 0;
        velocity.y = 0;
        if (state[SDL_SCANCODE_LEFT])  velocity.x -= 1;
        if (state[SDL_SCANCODE_RIGHT]) velocity.x += 1;
        if (state[SDL_SCANCODE_UP])    velocity.y -= 1;
        if (state[SDL_SCANCODE_DOWN])  velocity.y += 1;

        position.x += velocity.x * speed * deltaTime;
        position.y += velocity.y * speed * deltaTime;
    }
};

#endif