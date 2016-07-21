#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
using namespace std;
//standard library
#ifndef _BLOCK_H_
#define _BLOCK_H_
class BLOCK{
    private:
    int size_row;
    int size_col;
    int cur_row;
    int cur_col;
    char* mode;
    public:
    char*** content;
    BLOCK(int, int, char*);
    BLOCK();
    void print_block(int corner_row, int corner_col, int from_row,int from_col, int to_row, int to_col, char* mode);
    void type();
    void free_block();
    int get_size_row();
    int get_size_col();
    int start_row;
    int start_col;
};

void make_maze(char*** content,int size_row,int size_col,int row,int col);

void gotorc(int rpos, int cpos);

void ShowConsoleCursor(bool showFlag);

void SetColor(int f,int b);

void SetColor();
#endif
