#include ".\\Block.h"
#include ".\\Action.h"


BLOCK::BLOCK(int input_size_row,int input_size_col,char* input_mode){
    size_row=input_size_row;
    size_col=input_size_col;
    mode=input_mode;
    char** body;
    body=(char**)malloc(sizeof(char*)*input_size_row*input_size_col);
    content=(char***)malloc(sizeof(char**)*input_size_row);
    for(int count=0;count<input_size_row;count++)
        content[count]=body+input_size_row*count;
    if(strcmp("map",input_mode)==0){
        for(int count=0;count<input_size_row;count++)
        for(int count2=0;count2<input_size_col;count2++){
            content[count][count2]="map";
        }
    }
    if(strcmp("maze",input_mode)==0){
        for(int count=0;count<input_size_row;count++)
        for(int count2=0;count2<input_size_col;count2++){
            content[count][count2]="wall";
        }
        int row,col;
        row=rand()%(size_row-2)+1;
        col=rand()%(size_col-2)+1;
        start_row=row;
        start_col=col;
        make_maze(content,size_row,size_col,row,col);
    }
    if(strcmp("board",input_mode)==0){
        for(int count=0;count<input_size_row;count++)
        for(int count2=0;count2<input_size_col;count2++){
            content[count][count2]="blank";
        }
        cur_row=1;
        cur_col=1;
    }
}

BLOCK::BLOCK(){
    BLOCK(10,10,"board");
}

void make_maze(char*** content, int size_row, int size_col, int row, int col){
    int stuck=0;
    if(row<0||size_row<=row) return;
    if(col<0||size_col<=col) return;
    if((row+1<0||size_row<=row+1)||strcmp("blank",content[row+1][col])==0) stuck++;
    if((row-1<0||size_row<=row-1)||strcmp("blank",content[row-1][col])==0) stuck++;
    if((col+1<0||size_col<=col+1)||strcmp("blank",content[row][col+1])==0) stuck++;
    if((col-1<0||size_col<=col-1)||strcmp("blank",content[row][col-1])==0) stuck++;
    if(stuck>=2)
        return;
    content[row][col]="blank";
    // to see if the moving is stuck
    // where stuck means that
    // stepping out of board
    // or stepping the old path
    // if stuck, then return
    // else, step with blank as a foot print


    int seq[4]={0},direction_r,temp;

    for(int count=0;count<4;count++){
        temp=rand()%(4-count)+1;
        direction_r=-1;
        for(int count2=1;count2<=temp;count2++){
            direction_r++;
            if(seq[direction_r]==1) count2--;
        }
        seq[direction_r]=1;
        switch(direction_r){
            case 0:
                make_maze(content,size_row,size_col,row+1,col);
            break;
            case 1:
                make_maze(content,size_row,size_col,row-1,col);
            break;
            case 2:
                make_maze(content,size_row,size_col,row,col+1);
            break;
            case 3:
                make_maze(content,size_row,size_col,row,col-1);
            break;
            default:
                printf("error");
            break;
        }
    }
}

void BLOCK::print_block(int corner_row, int corner_col, int from_row,int from_col, int to_row, int to_col, char* input_mode){
    int size_row;
    int size_col;
    size_row=to_row-from_row+1;
    size_col=to_col-from_col+1;
    int row_space;
    int col_space;
    if(strcmp("graphic", input_mode)==0){
        row_space=1;
        col_space=2;
    }
    if(strcmp("text", input_mode)==0){
        row_space=1;
        col_space=1;
    }
    for(int count=0;count<size_row;count++)
    for(int count2=0;count2<size_col;count2++){
        gotorc(corner_row+count*row_space,corner_col+count2*col_space);
        if(strcmp("wall",content[from_row+count][from_col+count2])==0){
            int color=rand()%2+4;
            SetColor(color,color);
            puts("# ");
            SetColor();

        }
        else if(strcmp("blank",content[from_row+count][from_col+count2])==0)
            puts("  ");
        else if(strcmp("map",content[from_row+count][from_col+count2])==0)
            puts("  ");
        else if(strcmp("enemy",content[from_row+count][from_col+count2])==0)
            puts("& ");
        else if(strcmp("grass",content[from_row+count][from_col+count2])==0)
            puts("* ");
        else if(strcmp("player",content[from_row+count][from_col+count2])==0)
            puts("@ ");
        else if(strcmp("end",content[from_row+count][from_col+count2])==0){
            SetColor(rand()%7+1,0);
            puts("O ");
            SetColor();
        }
        else{
            putc(content[from_row+count][from_col+count2][0],stdout);
        }
    }

}

void gotorc(int rpos, int cpos){
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = cpos; scrn.Y = rpos;
  SetConsoleCursorPosition(hOuput,scrn);
}

void ShowConsoleCursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void BLOCK::free_block(){
    free(content[0]);
    free(content);
}

int BLOCK::get_size_row(){
    return size_row;
}

int BLOCK::get_size_col(){
    return size_col;
}

void mark_end(BLOCK maze){
    int legal_space=0;
    int random;
    for(int count=1;count<=maze.get_size_row()*maze.get_size_col();count++){
        if(strcmp("blank",maze.content[count%maze.get_size_row()][count/maze.get_size_row()])==0)
            legal_space++;
        if(strcmp("grass",maze.content[count%maze.get_size_row()][count/maze.get_size_row()])==0)
            legal_space++;
    }
    random=rand()%legal_space;
    int temp=0;
    for(int count=temp=0;count<random;temp++,count++){
        if(strcmp("blank",maze.content[temp%maze.get_size_row()][temp/maze.get_size_row()])==0)
            count++;
        if(strcmp("grass",maze.content[temp%maze.get_size_row()][temp/maze.get_size_row()])==0)
            count++;
    }
    maze.content[random%maze.get_size_row()][random/maze.get_size_row()]="end";
}

void SetColor(int f,int b){
    unsigned short ForeColor=f+16*b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}

void SetColor(){
    SetColor(7,0);
}
