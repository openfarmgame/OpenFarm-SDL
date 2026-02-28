#include <stdio.h>
#include <assert.h>

#include "conveyor.h"

// 헬퍼 함수: 테스트 결과 출력
void test_case(int up, int down, int left, int right, int expected, const char* desc) {
    int result = ConveyorConnect(up, down, left, right);
    printf("Test: %s -> ", desc);
    if(result == expected) {
        printf("PASSED\n");
    } else {
        printf("FAILED (expected %d, got %d)\n", expected, result);
    }
    assert(result == expected);
}

int main() {
    // 수직: │
    test_case(1, 1, 0, 0, 0, "Vertical conveyor");
    
    // 수평: ─
    test_case(0, 0, 1, 1, 1, "Horizontal conveyor");
    
    // ┌ : 아래, 오른쪽
    test_case(0, 1, 0, 1, 2, "Top-left corner");
    
    // ┐ : 아래, 왼쪽
    test_case(0, 1, 1, 0, 3, "Top-right corner");
    
    // └ : 위, 오른쪽
    test_case(1, 0, 0, 1, 4, "Bottom-left corner");
    
    // ┘ : 위, 왼쪽
    test_case(1, 0, 1, 0, 5, "Bottom-right corner");
    
    // 블록 없음
    test_case(0, 0, 0, 0, 0, "No connections");
    // 단일 연결
    test_case(1, 0, 0, 0, 0, "Single up connection");
    test_case(0, 1, 0, 0, 0, "Single down connection");
    test_case(0, 0, 0, 1, 1, "Single right connection");
    test_case(0, 0, 1, 0, 1, "Single left connection");
    
    printf("All tests completed.\n");
    return 0;
}