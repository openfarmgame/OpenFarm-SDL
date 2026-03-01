#include "tilemap.h"

// 생성자에서 벡터 크기를 미리 할당해둡니다 (메모리 최적화)
TileMap::TileMap(int w, int h) : width(w), height(h), tiles(w * h, 0) {}

bool TileMap::IsValid(int x, int y) const {
    return (x >= 0 && x < width && y >= 0 && y < height);
}

int TileMap::GetTile(int x, int y) const {
    if (!IsValid(x, y)) return -1; // 유효하지 않은 좌표는 -1 반환
    
    return tiles[y * width + x];
}

void TileMap::SetTile(int x, int y, int value) {
    if (IsValid(x, y)) {
        tiles[y * width + x] = value;
    }
}