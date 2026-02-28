#include <string_view>
#include <array>
#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils.h"
#include "player.hpp"

constexpr int  SCREEN_WIDTH      = 960;
constexpr int  SCREEN_HEIGHT     = 640;
constexpr int  TILE_SIZE         = 32;
constexpr std::string_view TITLE = "Perfectory alpha 1.0";

constexpr int MAP_WIDTH  = (SCREEN_WIDTH / TILE_SIZE);
constexpr int MAP_HEIGHT = (SCREEN_HEIGHT / TILE_SIZE);

SDL_Color sky = {113, 199, 245, 255}; // NOLINT

namespace {
    SDL_Resources Init() {
        SDL_Resources res{nullptr, nullptr};

        SDL_SetHint("SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR", "0");

        // SDL Init

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
            return res; 
        }

        // SDL_image Init

        const int IMG_FLAGS = IMG_INIT_PNG;
        if ((IMG_Init(IMG_FLAGS) & IMG_FLAGS) == 0) {
            std::cerr << "SDL_image Error: " << IMG_GetError() << "\n";
            return res;
        }

        // Create Window and Renderer

        res.window = SDL_CreateWindow(TITLE.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0); // NOLINT
        if (res.window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
            return res;
        }

        res.renderer = SDL_CreateRenderer(res.window, -1, SDL_RENDERER_ACCELERATED);
        if (res.renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
            return res;
        }

        return res;
    }

    int GetTile(MapData<MAP_WIDTH, MAP_HEIGHT>& map, int x, int y) {
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
            return map[x][y]; // NOLINT
        }
            
        return 0;
    }
}

int main() {
    bool running = true;
    SDL_Rect dst;

    // Map Init
    MapData<MAP_WIDTH, MAP_HEIGHT> ground_map;

    for (auto& row : ground_map) {
        row.fill(1); // fill 1 all tiles
    }
    
    // Init
    const SDL_Resources RES = Init();

    if (RES.window == nullptr || RES.renderer == nullptr) {
        SDL_DestroyRenderer(RES.renderer); 
        SDL_DestroyWindow(RES.window);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Load image
    SDL_Texture *grass_image = LoadImage(RES.renderer, "assets/grass.png");
    SDL_Texture *bnf_image = LoadImage(RES.renderer, "assets/bnf.png");
    SDL_Texture *player_image = LoadImage(RES.renderer, "assets/player.png");
    SDL_Texture *font_image = LoadImage(RES.renderer, "assets/font.png");

    // Player
    constexpr int PLAYER_SIZE = 32;
    constexpr int PLAYER_POS = 10;
    Player player(PLAYER_POS, PLAYER_POS, player_image, PLAYER_SIZE, PLAYER_SIZE);

    // Clock
    const int FPS = 100;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;

    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime = 0;
    float deltaTime = 0;


    SDL_Event event;
    while (running)
    {
        frameStart = SDL_GetTicks();

        lastTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;

        // Update
        player.Update(deltaTime);

        while (SDL_PollEvent(&event) == 1)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    
                default:
                    break;
            }
            //player.Move(event);
        }
        
        SetColor(RES.renderer, sky);
        SDL_RenderClear(RES.renderer);

        for (int x = 0; x < MAP_WIDTH; x++) {
            for (int y = 0; y < MAP_HEIGHT; y++) {
                dst.x = x * TILE_SIZE;
                dst.y = y * TILE_SIZE;
                dst.w = TILE_SIZE;
                dst.h = TILE_SIZE;
                
                switch (GetTile(ground_map, x, y)) {
                    case 0: 
                        break;
                    case 1:
                        SDL_RenderCopy(RES.renderer, grass_image, nullptr, &dst);
                        break;
                    default:
                        SDL_RenderCopy(RES.renderer, bnf_image, nullptr, &dst);
                        break;
                }
            }
        }
        
        player.Draw(RES.renderer);

        RenderText(RES.renderer, font_image, "Perfectory alpha 1.0", 5, 0, 1, 1, 1, {0,0,0});

        SDL_RenderPresent(RES.renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyRenderer(RES.renderer);
    SDL_DestroyWindow(RES.window);
    
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
