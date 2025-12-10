#include"board/board.h"
#include"display/display.h"

Board board;
int main(){
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    boardInit(&board);
    showWelcomeMsg();
    showBoard(&board);
    return 0;
}