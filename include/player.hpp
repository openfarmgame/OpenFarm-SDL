#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

class Player {
private:
    Vector2<float> position;
    Vector2<float> velocity;
    SDL_Texture *texture;
    Vector2<int> size;
    SDL_Rect dst;
    const int speed = 150;
    Action action = REST;
    steady_clock::time_point lasttime;

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
        // Walk
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        velocity.x = 0;
        velocity.y = 0;
        if (state[SDL_SCANCODE_A])  velocity.x -= 1;
        if (state[SDL_SCANCODE_D]) velocity.x += 1;
        if (state[SDL_SCANCODE_W])    velocity.y -= 1;
        if (state[SDL_SCANCODE_S])  velocity.y += 1;

        velocity.normalize();
        
        position.x += velocity.x * speed * deltaTime;
        position.y += velocity.y * speed * deltaTime;

        // Action
        switch (action)
        {
        case FARMING:
        {
            auto now = steady_clock::now();

            // 5초 지났는지 확인
            if (now - lasttime >= 1000ms)
            {
                action = REST;
                lasttime = now;
            }
            break;
        }

        default:
            break;
        }
    }

    Vector2<int> GetTilePos() {
        return {
            static_cast<int>((position.x + (size.x / 2.0f)) / TILE_SIZE),
            static_cast<int>((position.y + (size.y / 2.0f)) / TILE_SIZE)
        };
    }

    Vector2<float> GetPos() {
        return position;
    }

    bool CanAction() const {
        return action == REST;
    }

    void Farming() {
        action = FARMING;
    }
};

#endif