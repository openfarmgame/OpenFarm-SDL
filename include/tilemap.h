#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>

class TileMap {
private:
    int width;
    int height;
    std::vector<int> tiles;

public:
    // 생성자: 지도 크기 초기화
    TileMap(int w, int h);

    // 타일 가져오기
    int GetTile(int x, int y) const;

    // 타일 설정하기
    void SetTile(int x, int y, int value);

    // 유틸리티: 좌표가 유효한지 확인
    bool IsValid(int x, int y) const;

    // Getter
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    auto begin() { return tiles.begin(); }
    auto end() { return tiles.end(); }
};

#endif // TILEMAP_H