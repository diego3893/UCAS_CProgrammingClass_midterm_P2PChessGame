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
    for(int i=0; i<=BOARD_SIZE; ++i){
        for(int j=0; j<=BOARD_SIZE; ++j){
            board->pieceColor[i][j] = BLANK;
        }
    }
    board->last_col = -1;
    board->last_row = -1;
    board->pieceTotal = 0;
    return;
}

bool transInput2Coord(const char s[], int* row, int* col){
    int row_temp, col_temp;
    if(strlen(s)<INPUT_MIN_LEN || strlen(s)>INPUT_MAX_LEN){
        return false;
    }
    if(!('A'<=s[0] && s[0]<='O') || !('0'<=s[1] && s[1]<='9')){
        return false;
    }
    col_temp = COL_FROM_CHAR(s[0]);
    if(strlen(s) == 3){
        if(!('0'<=s[2] && s[2]<='9')){
            return false;
        }
        row_temp = ROW_FROM_NUM(s[1])*10+ROW_FROM_NUM(s[2]);
    }else{
        row_temp = ROW_FROM_NUM(s[1]);
    }
    if(1<=row_temp && row_temp<=15){
        *col = col_temp;
        *row = row_temp;
        return true;
    }
    return false;
}

bool boardIsFull(const Board* board){
    if(board->pieceTotal == 255){
        return true;
    }
    return false;
}

bool isEmpty(const Board* board, int row, int col){
    if(board->pieceColor[row][col] == BLANK){
        return true;
    }
    return false;
}

Piece getPiece(const Board* board, int row, int col){
    return board->pieceColor[row][col];
}

int dropPiece(Board* board, int row, int col, Piece piece_color){
    if(!(1<=row && row<=15&& 1<=col && col<=15)){
        return -1;
    }
    if(!isEmpty(board, row, col)){
        return 0;
    }
    board->pieceColor[row][col] = piece_color;
    board->last_col = col;
    board->last_row = row;
    board->pieceTotal++;
    return 1;
}