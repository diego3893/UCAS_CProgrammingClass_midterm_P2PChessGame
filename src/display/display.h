/**
 * @file display.h
 * @author diego3893 (diegozcx@foxmail.com)
 * @brief 棋盘显示相关头文件，使用UTF-8编码
 * @version 1.0
 * @date 2025-12-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#include<windows.h>
#include<stdio.h>
#include"../board/board.h"

#define PLAYER_BLACK 1 //黑方玩家
#define PLAYER_WHITE 2 //白方玩家
#define CROSS "\xE2\x94\xBC"
#define WHITE_PIECE "\xE2\x97\x8B"
#define BLACK_PIECE "\xE2\x97\x8F"
#define WHITE_PIECE_LAST "\xE2\x96\xB3"
#define BLACK_PIECE_LAST "\xE2\x96\xB2"
#define LEFT_TOP_CORNER "\xE2\x94\x8F"
#define RIGHT_TOP_CORNER "\xE2\x94\x93"
#define LEFT_BOTTOM_CORNER "\xE2\x94\x97"
#define RIGHT_BOTTOM_CORNER "\xE2\x94\x9B"
#define TOP_EDGE "\xE2\x94\xB3"
#define LEFT_EDGE "\xE2\x94\xA3"
#define RIGHT_EDGE "\xE2\x94\xAB"
#define BOTTOM_EDGE "\xE2\x94\xBB"

/**
 * @brief 显示棋盘
 * 
 * @param board 棋盘
 */
void showBoard(const Board* board);

void showInputPrompt(int current_player);

void showMessage(const char msg[]);

/**
 * @brief 开始游戏时的提示语
 * 
 */
void showWelcomeMsg();

void showGameOver(int result);

#endif 