#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "../src/board/board.h"
#include "../src/rule/rule.h"

#define ASSERT(expr, msg) \
    do { \
        if (!(expr)) { \
            printf("测试失败: %s\n", msg); \
            return false; \
        } \
    } while(0)

void initTestBoard(Board* board, Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1]) {
    boardInit(board);
    for (int i = 1; i <= BOARD_SIZE; i++) {
        for (int j = 1; j <= BOARD_SIZE; j++) {
            if (pieces[i][j] != BLANK) {
                dropPiece(board, i, j, pieces[i][j]);
            }
        }
    }
}

bool testFiveInRowVertical() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[3][5] = BLACK;
    pieces[4][5] = BLACK;
    pieces[5][5] = BLACK;
    pieces[6][5] = BLACK;
    pieces[7][5] = BLACK;
    initTestBoard(&board, pieces);

    int cnt = checkFiveInRow(&board, 5, 5, PLAYER_BLACK);
    ASSERT(cnt >= 1, "纵向五连判定失败");
    printf("测试通过: 纵向五连\n");
    return true;
}

bool testFiveInRowDiagonal1() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[3][3] = BLACK;
    pieces[4][4] = BLACK;
    pieces[5][5] = BLACK;
    pieces[6][6] = BLACK;
    pieces[7][7] = BLACK;
    initTestBoard(&board, pieces);

    int cnt = checkFiveInRow(&board, 5, 5, PLAYER_BLACK);
    ASSERT(cnt >= 1, "正斜向五连判定失败");
    printf("测试通过: 正斜向五连\n");
    return true;
}

bool testFiveInRowDiagonal2() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[3][7] = BLACK;
    pieces[4][6] = BLACK;
    pieces[5][5] = BLACK;
    pieces[6][4] = BLACK;
    pieces[7][3] = BLACK;
    initTestBoard(&board, pieces);

    int cnt = checkFiveInRow(&board, 5, 5, PLAYER_BLACK);
    ASSERT(cnt >= 1, "反斜向五连判定失败");
    printf("测试通过: 反斜向五连\n");
    return true;
}

bool testLongChainVertical() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[2][5] = BLACK;
    pieces[3][5] = BLACK;
    pieces[4][5] = BLACK;
    pieces[5][5] = BLACK;
    pieces[6][5] = BLACK;
    pieces[7][5] = BLACK;
    initTestBoard(&board, pieces);

    int cnt = checkLongChain(&board, 5, 5);
    ASSERT(cnt >= 1, "纵向长连判定失败");
    printf("测试通过: 纵向长连\n");
    return true;
}

bool testLongChainDiagonal() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[2][2] = BLACK;
    pieces[3][3] = BLACK;
    pieces[4][4] = BLACK;
    pieces[5][5] = BLACK;
    pieces[6][6] = BLACK;
    pieces[7][7] = BLACK;
    initTestBoard(&board, pieces);

    int cnt = checkLongChain(&board, 5, 5);
    ASSERT(cnt >= 1, "斜向长连判定失败");
    printf("测试通过: 斜向长连\n");
    return true;
}

bool testDoubleLiveThree1() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[5][3] = BLACK;
    pieces[5][4] = BLACK;
    pieces[3][3] = BLACK;
    pieces[4][4] = BLACK;
    pieces[5][5] = BLACK;
    initTestBoard(&board, pieces);

    int shape_cnt[CHESS_SHAPE_CNT] = {0};
    checkChessShape(&board, 5, 5, shape_cnt, PLAYER_BLACK);
    ASSERT(shape_cnt[LIVE_THREE] >= 2 && isForbiddenMove(shape_cnt), "横向+斜向双活三判定失败");
    printf("测试通过: 横向+斜向双活三\n");
    return true;
}

bool testDoubleLiveThree2() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[5][2] = BLACK;
    pieces[5][4] = BLACK;
    pieces[3][5] = BLACK;
    pieces[4][5] = BLACK;
    pieces[5][5] = BLACK;
    initTestBoard(&board, pieces);

    int shape_cnt[CHESS_SHAPE_CNT] = {0};
    checkChessShape(&board, 5, 5, shape_cnt, PLAYER_BLACK);
    ASSERT(shape_cnt[LIVE_THREE] >= 2 && isForbiddenMove(shape_cnt), "跳活三+普通活三判定失败");
    printf("测试通过: 跳活三+普通活三\n");
    return true;
}

bool testDoubleLiveFour() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[5][2] = BLACK;
    pieces[5][3] = BLACK;
    pieces[5][4] = BLACK;
    pieces[2][5] = BLACK;
    pieces[3][5] = BLACK;
    pieces[4][5] = BLACK;
    pieces[5][5] = BLACK; 
    initTestBoard(&board, pieces);

    int shape_cnt[CHESS_SHAPE_CNT] = {0};
    checkChessShape(&board, 5, 5, shape_cnt, PLAYER_BLACK);
    ASSERT((shape_cnt[LIVE_FOUR] >= 2) && isForbiddenMove(shape_cnt), "双活四判定失败");
    printf("测试通过: 双活四\n");
    return true;
}

bool testLiveFourPlusBreakthrough() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[5][2] = BLACK;
    pieces[5][3] = BLACK;
    pieces[5][4] = BLACK;
    pieces[2][5] = BLACK;
    pieces[3][5] = BLACK;
    pieces[4][5] = BLACK;
    pieces[6][5] = WHITE;  
    pieces[5][5] = BLACK; 
    initTestBoard(&board, pieces);

    int shape_cnt[CHESS_SHAPE_CNT] = {0};
    checkChessShape(&board, 5, 5, shape_cnt, PLAYER_BLACK);
    ASSERT((shape_cnt[LIVE_FOUR] >= 1 && shape_cnt[BREAKTHROUGH_FOUR] >= 1) && isForbiddenMove(shape_cnt), "活四+冲四判定失败");
    printf("测试通过: 活四+冲四\n");
    return true;
}

bool testDoubleBreakthroughFour() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[5][2] = BLACK;
    pieces[5][3] = BLACK;
    pieces[5][4] = BLACK;
    pieces[5][6] = WHITE; 
    pieces[2][5] = BLACK;
    pieces[3][5] = BLACK;
    pieces[4][5] = BLACK;
    pieces[6][5] = WHITE;  
    pieces[5][5] = BLACK; 
    initTestBoard(&board, pieces);

    int shape_cnt[CHESS_SHAPE_CNT] = {0};
    checkChessShape(&board, 5, 5, shape_cnt, PLAYER_BLACK);
    ASSERT(shape_cnt[BREAKTHROUGH_FOUR] >= 2 && isForbiddenMove(shape_cnt), "普通双冲四判定失败");
    printf("测试通过: 普通双冲四\n");
    return true;
}

bool testDoubleBreakthroughFour2() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[5][2] = BLACK;
    pieces[5][3] = BLACK;
    pieces[5][4] = BLACK;
    pieces[5][6] = BLACK; 
    pieces[5][8] = BLACK;
    pieces[5][9] = BLACK;
    pieces[5][10] = BLACK;
    initTestBoard(&board, pieces);

    int shape_cnt[CHESS_SHAPE_CNT] = {0};
    checkChessShape(&board, 5, 6, shape_cnt, PLAYER_BLACK);
    ASSERT(shape_cnt[BREAKTHROUGH_FOUR] >= 2 && isForbiddenMove(shape_cnt), "双向二跳四判定失败");
    printf("测试通过: 双向二跳四\n");
    return true;
}

bool testSpecialBreakthroughFour() {
    Board board;
    Piece pieces[BOARD_SIZE+1][BOARD_SIZE+1] = {0};
    pieces[5][1] = BLACK;
    pieces[5][2] = BLACK;
    pieces[5][3] = BLACK;
    pieces[5][4] = BLACK; 
    pieces[5][6] = BLACK;
    pieces[6][5] = BLACK;
    pieces[6][6] = BLACK;
    pieces[6][7] = BLACK;
    pieces[6][8] = BLACK;
    initTestBoard(&board, pieces);

    int shape_cnt[CHESS_SHAPE_CNT] = {0};
    checkChessShape(&board, 6, 8, shape_cnt, PLAYER_BLACK);
    ASSERT(shape_cnt[BREAKTHROUGH_FOUR] >= 1 && isForbiddenMove(shape_cnt), "特殊冲四（单边禁手）判定失败");
    printf("测试通过: 特殊冲四（单边禁手）\n");
    return true;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    printf("===== 开始测试规则模块 =====\n");
    bool all_pass = true;

    all_pass &= testFiveInRowVertical();
    all_pass &= testFiveInRowDiagonal1();
    all_pass &= testFiveInRowDiagonal2();

    all_pass &= testLongChainVertical();
    all_pass &= testLongChainDiagonal();

    all_pass &= testDoubleLiveThree1();
    all_pass &= testDoubleLiveThree2();

    all_pass &= testDoubleLiveFour();
    all_pass &= testLiveFourPlusBreakthrough();
    all_pass &= testDoubleBreakthroughFour();
    all_pass &= testDoubleBreakthroughFour2();
    all_pass &= testSpecialBreakthroughFour();

    printf("\n===== 测试结束 =====\n");
    if (all_pass) {
        printf("所有测试通过！\n");
    } else {
        printf("部分测试失败，请检查代码。\n");
    }
    system("pause");
    return 0;
}