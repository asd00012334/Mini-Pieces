#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
using namespace std;
//standard library
#include ".\\Block.h"
#ifndef _ACTION_H_
class OBJECT{
    protected:
        char* mode;
    public:
        int location_row;
        int location_col;
        int value;
        int exp;
        int durability;
        int inheribility;
        int up,down,left,right;
        OBJECT(char* input_mode);
        OBJECT(char* input_mode,int input_location_row,int input_location_col,
               int input_up, int input_down, int input_left, int input_right);
        char* content[2][10];// row 1 is for basic quality
                             // row 2 is for belonings
};

void mark_end(BLOCK maze);

int move_legal(int step_num, char* direction, OBJECT object, BLOCK map);
#endif
