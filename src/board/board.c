/**
 * @file board.c
 * @author diego3893 (diegozcx@foxmail.com)
 * @brief 棋盘相关函数具体实现
 * @version 1.0
 * @date 2025-12-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include"board.h"

/**
 * @brief 初始化棋盘，将所有位置初始化为空，最新落子为-1（未落子），总落子数为0
 * 
 * @param board 棋盘
 */
void boardInit(Board* board){
    if(board == NULL){
        return;
    }
    for(int i=0; i<BOARD_SIZE; ++i){
        for(int j=0; j<BOARD_SIZE; ++j){
            board->pieceColor[i][j] = BLANK;
        }
    }
    board->last_col = -1;
    board->last_row = -1;
    board->pieceTotal = 0;
    return;
}