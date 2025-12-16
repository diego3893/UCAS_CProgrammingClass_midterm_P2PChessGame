#include "rule.h"

/*
跳四（冲四）判断/双向判断
*/

GameStatus judgeStatus(const Board* board, int row, int col, Player current_player){
    int five_count = checkFiveInRow(board, row, col, current_player);
    if(five_count > 0){
        if(current_player == PLAYER_WHITE){
            return WHITE_WIN;
        }else{
            return BLACK_WIN;
        }
    }
    if(current_player == PLAYER_BLACK){
        int chess_shape_cnt[CHESS_SHAPE_CNT] = {0};
        checkChessShape(board, row, col, chess_shape_cnt, current_player);
        if(isForbiddenMove(chess_shape_cnt)){
            return FORBIDDEN_MOVE;
        }
    }
    if(boardIsFull(board)){
        return DRAW;
    }
    return PLAYING;
}

void checkChessShape(const Board* board, int row, int col, int chess_shape_cnt[], Player current_player){
    for(int i=0; i<CHESS_SHAPE_CNT; ++i){
        chess_shape_cnt[i] = 0;
    }
    //chess_shape_cnt[LIVE_THREE] = checkLiveThree(board, row, col);
    chess_shape_cnt[LIVE_FOUR] = checkLiveFour(board, row, col);
    //chess_shape_cnt[BREAKTHROUGH_FOUR] = checkBreakthroughFour(board, row, col);
    chess_shape_cnt[LONG_CHAIN] = checkLongChain(board, row, col);
    chess_shape_cnt[FIVE_IN_ROW] = checkFiveInRow(board, row, col, current_player);
    return;
}

int checkFiveInRow(const Board* board, int row, int col, Player current_player){
    Piece color = (current_player==PLAYER_BLACK) ? BLACK : WHITE;
    Pair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;
    for(int i=0; i<4; ++i){
        int dx = dirs[i].x;
        int dy = dirs[i].y;
        int length = 1;
        int x = row+dx;
        int y = col+dy;
        while(x>=1 && x<=BOARD_SIZE && y>= 1&& y<=BOARD_SIZE && getPiece(board, x, y)==color){
            length++;
            x += dx;
            y += dy;
        }
        x = row-dx;
        y = col-dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==color){
            length++;
            x -= dx;
            y -= dy;
        }
        if(current_player == PLAYER_BLACK){
            if(length == 5){
                cnt++;
            }
        }else{
            if(length >= 5){
                cnt++;
            }
        }
    }
    return cnt;
}

int checkLongChain(const Board* board, int row, int col){
    Piece color = BLACK;
    Pair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;
    for(int i=0; i<4; ++i){
        int dx = dirs[i].x;
        int dy = dirs[i].y;
        int length = 1;
        int x = row+dx;
        int y = col+dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==color){
            length++;
            x += dx;
            y += dy;
        }
        x = row-dx;
        y = col-dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==color){
            length++;
            x -= dx;
            y -= dy;
        }
        if(length >= 6){
            cnt++;
        }
    }
    return cnt;
}

int checkLiveThree(const Board* board, int row, int col){
    Piece color = BLACK;
    Piece p;
    Pair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;
    for(int i=0; i<4; ++i){
        bool flag_can_form_live_four = false;
        int dx = dirs[i].x;
        int dy = dirs[i].y;
        int same = 1; 
        int blank_ends = 0;
        int x = row+dx;
        int y = col+dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE){
            p = getPiece(board, x, y);
            if(p == color){
                same++;
                x += dx;
                y += dy;
            }else if(p == BLANK){
                if(!isForbiddenPosition(board, x, y)){
                    blank_ends++;
                    if(checkCanFormLiveFour(board, x, y, dirs[i])){
                        flag_can_form_live_four = true;
                    }
                }
                break;
            }else{
                break;
            }
        }
        x = row-dx;
        y = col-dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE){
            p = getPiece(board, x, y);
            if(p == color){
                same++;
                x -= dx;
                y -= dy;
            }else if(p == BLANK){
                if(!isForbiddenPosition(board, x, y)){
                    blank_ends++;
                    if(checkCanFormLiveFour(board, x, y, dirs[i])){
                        flag_can_form_live_four = true;
                    }
                }
                break;
            }else{
                break;
            }
        }
        if(same==3 && blank_ends==2 && flag_can_form_live_four){
            cnt++;
        }else if(same==2 && blank_ends==2 && flag_can_form_live_four){
            cnt++;
        }else if(same==1 && blank_ends==2 && flag_can_form_live_four){
            cnt++;
        }
    }
    return cnt;
}

int checkLiveFour(const Board* board, int row, int col){
    Piece color = BLACK;
    Pair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;
    for(int i=0; i<4; ++i){
        Pair blank_coord[2] = {0};
        int Index = 0;
        int dx = dirs[i].x;
        int dy = dirs[i].y;
        int same = 1; 
        int blank_ends = 0;
        int x = row+dx;
        int y = col+dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==color){
            same++;
            x += dx;
            y += dy;
        }
        if(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==BLANK){
            blank_ends++;
            blank_coord[Index].x = x, blank_coord[Index++].y = y;
        }
        x = row-dx;
        y = col-dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==color){
            same++;
            x -= dx;
            y -= dy;
        }
        if(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==BLANK){
            blank_ends++;
            blank_coord[Index].x = x, blank_coord[Index++].y = y;
        }
        if(same==4 && blank_ends==2){
            if(!isForbiddenPosition(board, blank_coord[0].x, blank_coord[0].y)&&
                !isForbiddenPosition(board, blank_coord[1].x, blank_coord[1].y)){
                    cnt++;
            }
        }
    }
    return cnt;
}

int checkBreakthroughFour(const Board* board, int row, int col){
    Piece color = BLACK;
    Piece opp_color = WHITE;
    Piece p;
    Pair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;
    for(int i=0; i<4; ++i){
        int dx = dirs[i].x;
        int dy = dirs[i].y;
        int same = 1; 
        int blocks = 0; 
        int blanks = 0; 
        int x = row+dx;
        int y = col+dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE){
            p = getPiece(board, x, y);
            if(p == color){
                same++;
                x += dx;
                y += dy;
            }else if(p == opp_color){
                blocks++;
                break;
            }else{
                if(!isForbiddenPosition(board, x, y)){
                    blanks++;
                }else{
                    blocks++;
                }
                break;
            }
        }
        x = row-dx;
        y = col-dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE){
            p = getPiece(board, x, y);
            if(p == color){
                same++;
                x -= dx;
                y -= dy;
            }else if(p == opp_color){
                blocks++;
                break;
            }else{
                if(!isForbiddenPosition(board, x, y)){
                    blanks++;
                }else{
                    blocks++;
                }
                break;
            }
        }
        if(same == 4 && blocks == 1 && blanks == 1){
            cnt++;
        }
    }
    return cnt;
}

bool isForbiddenMove(const int chess_shape_cnt[]){
    if(chess_shape_cnt[LONG_CHAIN] > 0){
            return true;
    }
    if(chess_shape_cnt[LIVE_THREE] >= 2){
        return true;
    }
    if(chess_shape_cnt[LIVE_FOUR]+chess_shape_cnt[BREAKTHROUGH_FOUR] >= 2){
        return true;
    }
    return false;
}

bool isForbiddenPosition(const Board* board, int row, int col){
    if(row<1 || row>BOARD_SIZE || col<1 || col>BOARD_SIZE){
        return false;
    }
    if(getPiece(board, row, col) != BLANK){
        return false;
    }
    Board temp_board;
    memcpy(&temp_board, board, sizeof(Board));
    if(dropPiece(&temp_board, row, col, BLACK) != 1){
        return false; 
    }
    int chess_shape_cnt[CHESS_SHAPE_CNT] = {0};
    checkChessShape(&temp_board, row, col, chess_shape_cnt, PLAYER_BLACK);
    return isForbiddenMove(chess_shape_cnt);
}

bool checkCanFormLiveFour(const Board* board, int row, int col, Pair dir){
    if (getPiece(board, row, col) != BLANK) {
        return 0;
    }
    Piece color = BLACK, opp_color = WHITE;
    int dx = dir.x;
    int dy = dir.y;
    int same = 1; 
    int blank_ends = 0;
    int x = row+dx;
    int y = col+dy;
    while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==color){
        same++;
        x += dx;
        y += dy;
    }
    if(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==BLANK){
        if(!isForbiddenPosition(board, x, y)){
            blank_ends++;
        }
    }
    if(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==opp_color){
        return false;
    }
    x = row-dx;
    y = col-dy;
    while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==color){
        same++;
        x -= dx;
        y -= dy;
    }
    if(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==BLANK){
        if(!isForbiddenPosition(board, x, y)){
            blank_ends++;
        }
    }
    if(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE && getPiece(board, x, y)==opp_color){
        return false;
    }
    if(same==4 && blank_ends==2){
        return true;
    }
    return false;
}