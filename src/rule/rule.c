#include "rule.h"

/*
活三、活四、冲四判断，空白点判断是否为禁手位
考虑在棋盘中虚拟落子，判定结束后回溯？
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
    chess_shape_cnt[LIVE_THREE] = checkLiveThree(board, row, col);
    chess_shape_cnt[LIVE_FOUR] = checkLiveFour(board, row, col);
    chess_shape_cnt[BREAKTHROUGH_FOUR] = checkBreakthroughFour(board, row, col);
    chess_shape_cnt[LONG_CHAIN] = checkLongChain(board, row, col);
    chess_shape_cnt[FIVE_IN_ROW] = checkFiveInRow(board, row, col, current_player);
    return;
}

int checkFiveInRow(const Board* board, int row, int col, Player current_player){
    Piece color = (current_player==PLAYER_BLACK) ? BLACK : WHITE;
    DeltaPair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;
    for(int i=0; i<4; ++i){
        int dx = dirs[i].dx;
        int dy = dirs[i].dy;
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
    DeltaPair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;
    for(int i=0; i<4; ++i){
        int dx = dirs[i].dx;
        int dy = dirs[i].dy;
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
    Piece opp_color = WHITE;
    Piece p;

    DeltaPair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;

    for(int i=0; i<4; ++i){
        int dx = dirs[i].dx;
        int dy = dirs[i].dy;
        int same = 1;  // 当前位置算一个
        int blank_ends = 0;

        // 正向检查
        int x = row+dx;
        int y = col+dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE){
            p = getPiece(board, x, y);
            if(p == color){
                same++;
                x += dx;
                y += dy;
            }else if(p == BLANK){
                blank_ends++;
                break;
            }else{  // 对方棋子阻挡
                break;
            }
        }

        // 反向检查
        x = row-dx;
        y = col-dy;
        while(x>=1 && x<=BOARD_SIZE && y>=1 && y<=BOARD_SIZE){
            p = getPiece(board, x, y);
            if(p == color){
                same++;
                x -= dx;
                y -= dy;
            }else if(p == BLANK){
                blank_ends++;
                break;
            }else{  // 对方棋子阻挡
                break;
            }
        }

        // 活三：3个同色棋子且两端均为空白
        if(same == 3 && blank_ends == 2){
            cnt++;
        }
        // 跳活三：中间空一个的活三（如 X X _ X 形态）
        else if(same == 3 && blank_ends == 1){
            // 检查是否存在跳位空白
            int skip_x = row+dx * 2;
            int skip_y = col+dy * 2;
            if(skip_x >= 1 && skip_x <= BOARD_SIZE && skip_y >= 1 && skip_y <= BOARD_SIZE &&
                getPiece(board, skip_x, skip_y) == color &&
                getPiece(board, row+dx, col+dy) == BLANK){
                cnt++;
            }
        }
    }

    return cnt;
}

int checkLiveFour(const Board* board, int row, int col){
    Piece color = BLACK;
    DeltaPair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;
    for(int i=0; i<4; ++i){
        int dx = dirs[i].dx;
        int dy = dirs[i].dy;
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
        }
        if(same==4 && blank_ends==2){
            cnt++;
        }
    }
    return cnt;
}

int checkBreakthroughFour(const Board* board, int row, int col){
    Piece color = BLACK;
    Piece opp_color = WHITE;
    Piece p;
    DeltaPair dirs[] = {DELTA_RIGHT, DELTA_DOWN, DELTA_UPRIGHT, DELTA_DOWNRIGHT};
    int cnt = 0;
    int chess_shape_cnt = {0};
    for(int i=0; i<4; ++i){
        int dx = dirs[i].dx;
        int dy = dirs[i].dy;
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
                blanks++;
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
                blanks++;
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