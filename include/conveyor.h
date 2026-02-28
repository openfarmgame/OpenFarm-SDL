#ifndef CONVEYOR_H
#define CONVEYOR_H

typedef enum {
    CONV_VERTICAL = 0,        // │
    CONV_HORIZONTAL = 1,      // ─
    CONV_CORNER_TL = 2,       // ┌
    CONV_CORNER_TR = 3,       // ┐
    CONV_CORNER_BL = 4,       // └
    CONV_CORNER_BR = 5,       // ┘
} ConveyorShape;

typedef struct {
    int x, y;
    int dir; // 0: up, 1: down (0번 모양 기준)
} Conveyor;

ConveyorShape ConveyorConnect(int up, int down, int left, int right);
// input: 특정 컨베이어 블록을 기준으로 1칸 이내에 인접한 다른 컨베이어 블록을 나타냄. 컨베이어 벨트가 있으면 1, 없으면 0
// return: 정 가운데의 컨베이어 벨트의 방향을 리턴해야함 
// │ : 0, ─ : 1, ┌ : 2, ┐ : 3, └ : 4, ┘ : 5

#endif
