#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;
//standard library

#include ".\\Action.h"
#include ".\\Block.h"


int main() {
    int win=0;
    srand(time(NULL));
    printf("This is Ultimate Maze Solving!!\nPlease enter a level (from 1 to 10): ");
    int level;
    scanf("%d",&level);
    system("cls");
    level=25+25*level;
    BLOCK maze(level,level,"maze");
    OBJECT player("player",maze.start_row,maze.start_col,VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT);
    maze.content[player.location_row][player.location_col]="player";
    mark_end(maze);
    ShowConsoleCursor(false);
    while(1){
        Sleep(20);
        static int print_row_corner;
        static int print_col_corner;
        if(player.location_row-14<0)
            print_row_corner=0;
        else if(player.location_row+14>=maze.get_size_row())
            print_row_corner=maze.get_size_row()-29;
        else
            print_row_corner=player.location_row-14;

        if(player.location_col-14<0)
            print_col_corner=0;
        else if(player.location_col+14>=maze.get_size_col())
            print_col_corner=maze.get_size_col()-29;
        else
            print_col_corner=player.location_col-14;

        maze.print_block(1,1,print_row_corner,print_col_corner,print_row_corner+28,print_col_corner+28,"graphic");

        if(GetAsyncKeyState(VK_ESCAPE))
            break;
        if(GetAsyncKeyState(player.up)){
            if(move_legal(1,"up",player,maze)==-1){
                win=1;
                break;
            }
            if(move_legal(1,"up",player,maze)){
                maze.content[player.location_row][player.location_col]="blank";
                player.location_row--;
                maze.content[player.location_row][player.location_col]="player";
            }
        }
        if(GetAsyncKeyState(player.down)){
            if(move_legal(1,"down",player,maze)==-1){
                win=1;
                break;
            }
            if(move_legal(1,"down",player,maze)){
                maze.content[player.location_row][player.location_col]="blank";
                player.location_row++;
                maze.content[player.location_row][player.location_col]="player";
            }
        }
        if(GetAsyncKeyState(player.left)){
            if(move_legal(1,"left",player,maze)==-1){
                win=1;
                break;
            }
            if(move_legal(1,"left",player,maze)){
                maze.content[player.location_row][player.location_col]="blank";
                player.location_col--;
                maze.content[player.location_row][player.location_col]="player";
            }
        }
        if(GetAsyncKeyState(player.right)){
            if(move_legal(1,"right",player,maze)==-1){
                win=1;
                break;
            }
            if(move_legal(1,"right",player,maze)){
                maze.content[player.location_row][player.location_col]="blank";
                player.location_col++;
                maze.content[player.location_row][player.location_col]="player";
            }
        }
    }
    maze.free_block();
    system("cls");
    if(win){
        printf("You win!!\n");
    }else
        printf("You Lose!!\n");
    system("pause");
}
