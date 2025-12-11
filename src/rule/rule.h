#ifndef RULE_H
#define RULE_H

#include"../board/board.h"
#include"../display/display.h"

typedef struct{
    int dx;
    int dy;
}DeltaPair;

typedef enum{
    LIVE_THREE,
    LIVE_FOUR,
    BREAKTHROUGH_FOUR,
    FIVE_IN_ROW,
    LONG_CHAIN,
    CHESS_SHAPE_CNT
}ChessShape;

#define DELTA_RIGHT ((DeltaPair){1, 0})   
#define DELTA_DOWN ((DeltaPair){0, -1})  
#define DELTA_LEFT ((DeltaPair){-1, 0}) 
#define DELTA_UP ((DeltaPair){0, 1}) 
#define DELTA_UPRIGHT ((DeltaPair){1, 1}) 
#define DELTA_UPLEFT ((DeltaPair){-1, 1}) 
#define DELTA_DOWNLEFT ((DeltaPair){-1, -1})
#define DELTA_DOWNRIGHT ((DeltaPair){1, -1})

GameStatus judgeResult(const Board* board, int row, int col, Player current_player);

void checkChessShape(const Board* board, int row, int col, int chess_shape_cnt[], Player current_player);

int checkLiveThree(const Board* board, int row, int col);

int checkLiveFour(const Board* board, int row, int col);

int checkBreakthroughFour(const Board* board, int row, int col);

int checkLongChain(const Board* board, int row, int col);

int checkFiveInRow(const Board* board, int row, int col);

#endif 