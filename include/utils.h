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
};

SDL_Texture* LoadImage(SDL_Renderer *renderer, const char *path);
void SetColor(SDL_Renderer* renderer, SDL_Color c);
Vector2<int> GetSize(SDL_Texture *texture);
void RenderText(SDL_Renderer *renderer, SDL_Texture *fontTexture, 
                 const char *text, int x, int y, int size, 
                 int space_x, int space_y, SDL_Color color);


constexpr int KEY_RIGHT = 1073741903;
constexpr int KEY_LEFT = 1073741904;
constexpr int KEY_DOWN = 1073741905;
constexpr int KEY_UP = 1073741906;

#endif