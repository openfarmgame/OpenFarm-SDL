#include "conveyor.h"

ConveyorShape ConveyorConnect(int up, int down, int left, int right) {
    int bits = (up << 3) | (down << 2) | (left << 1) | right;
    int count = up + down + left + right; // 접점 개수

    if (count == 0) {
        return CONV_VERTICAL;
    }
    else if (count == 1) {
        switch(bits) {
            case 0b1000: return CONV_VERTICAL;    // |
            case 0b0100: return CONV_VERTICAL;    // |
            case 0b0010: return CONV_HORIZONTAL;  // -
            case 0b0001: return CONV_HORIZONTAL;  // -
        }
    }
    else if (count == 2) {
        switch(bits) {
            case 0b1100: return CONV_VERTICAL;    // |
            case 0b0011: return CONV_HORIZONTAL;  // -
            case 0b1001: return CONV_CORNER_BL;   // └
            case 0b1010: return CONV_CORNER_BR;   // ┘
            case 0b0101: return CONV_CORNER_TL;   // ┌
            case 0b0110: return CONV_CORNER_TR;   // ┐
        }
    }

    return CONV_HORIZONTAL; // 기본값으로 수평 반환
}