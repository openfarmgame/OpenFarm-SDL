#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

constexpr int FONT_WIDTH = 8;
constexpr int FONT_HEIGHT = 16;
constexpr int FONTMAP_SIZE = 160;
constexpr int GRID_COLUMNS = 10; // 한 줄 글자 수

constexpr int  SCREEN_WIDTH      = 960;
constexpr int  SCREEN_HEIGHT     = 640;
constexpr int  TILE_SIZE         = 64;
constexpr std::string_view TITLE = "OpenFarm alpha 1.0";

constexpr int MAP_WIDTH  = (SCREEN_WIDTH / TILE_SIZE);
constexpr int MAP_HEIGHT = (SCREEN_HEIGHT / TILE_SIZE);

struct SDL_Resources {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

template <size_t Width, size_t Height>
using MapData = std::array<std::array<int, Height>, Width>;

template<typename T>
struct Vector2 {
    T x{};
    T y{};

    constexpr Vector2() = default;
    constexpr Vector2(T x, T y) : x(x), y(y) {}

    // 타입 변환 생성자
    template<typename U>
    explicit constexpr Vector2(const Vector2<U>& other)
        : x(static_cast<T>(other.x)),
          y(static_cast<T>(other.y)) {}

    // 사칙연산
    constexpr Vector2 operator+(const Vector2& r) const {
        return { x + r.x, y + r.y };
    }

    constexpr Vector2 operator-(const Vector2& r) const {
        return { x - r.x, y - r.y };
    }

    constexpr Vector2 operator*(const Vector2& r) const {
        return { x * r.x, y * r.y };
    }

    constexpr Vector2 operator/(const Vector2& r) const {
        return { x / r.x, y / r.y };
    }

    // 스칼라 연산
    constexpr Vector2 operator*(T s) const {
        return { x * s, y * s };
    }

    constexpr Vector2 operator/(T s) const {
        return { x / s, y / s };
    }

    // 복합 대입
    constexpr Vector2& operator+=(const Vector2& r) {
        x += r.x; y += r.y;
        return *this;
    }

    double length() const {
        return std::sqrt(static_cast<double>(x * x + y * y));
    }

    void normalize() {
        double len = length();
        if (len > 0) { // 0으로 나누기 방지
            x = static_cast<T>(x / len);
            y = static_cast<T>(y / len);
        }
    }

    Vector2<float> get_normalized() const {
        float len = std::sqrt(static_cast<float>(x * x + y * y));
        if (len > 0.0f) {
            return { static_cast<float>(x) / len, static_cast<float>(y) / len };
        }
        return { 0.0f, 0.0f };
    }
};

SDL_Texture* LoadImage(SDL_Renderer *renderer, const char *path);
void SetColor(SDL_Renderer* renderer, SDL_Color c);
Vector2<int> GetSize(SDL_Texture *texture);
void RenderText(SDL_Renderer *renderer, SDL_Texture *fontTexture, 
                 const char *text, int x, int y, int size, 
                 int space_x, int space_y, SDL_Color color);

enum Action {
    Farming
};

#endif