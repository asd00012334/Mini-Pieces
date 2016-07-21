#include ".\\Action.h"



OBJECT::OBJECT(char* input_mode, int input_location_row, int input_location_col,
               int input_up, int input_down, int input_left, int input_right){
    up=input_up;
    down=input_down;
    left=input_left;
    right=input_right;
    mode=input_mode;
    location_row=input_location_row;
    location_col=input_location_col;
    if(strcmp("player",mode)){
        value=0;
        exp=0;
        for(int count=0;count<20;count++)
        for(int count2=0;count2<20;count2++)
            content[0][0]="empty";
        durability=100;
        inheribility=10;
    }
    else if(strcmp("trader",mode)){
        value=1000;
        exp=1000;
        for(int count=0;count<20;count++)
        for(int count2=0;count2<20;count2++)
            content[0][0]="empty";
        durability=100;
        inheribility=-100;
    }
    else if(strcmp("enemy_1",mode)){
        value=20;
        exp=20;
        for(int count=0;count<20;count++)
        for(int count2=0;count2<20;count2++)
            content[0][0]="empty";
        durability=15;
        inheribility=100;
    }
    else if(strcmp("boss",mode)){
        value=2000;
        exp=2000;
        for(int count=0;count<20;count++)
        for(int count2=0;count2<20;count2++)
            content[0][0]="empty";
        durability=5000;
        inheribility=100;
    }
    else if(strcmp("ally",mode)){
        value=200;
        exp=200;
        for(int count=0;count<20;count++)
        for(int count2=0;count2<20;count2++)
            content[0][0]="empty";
        durability=100;
        inheribility=-100;
    }
}

OBJECT::OBJECT(char* input_mode){
    OBJECT(input_mode,0,0,VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT);
}

int move_legal(int step_num, char* direction, OBJECT object, BLOCK map){
    int legal=1;
    if(strcmp("up",direction)==0){
        if(object.location_row-step_num>=0)
        for(int count=1;count<=step_num;count++){
            char* temp=map.content[object.location_row-count][object.location_col];
            if(strcmp("grass",temp)!=0)
            if(strcmp("blank",temp)!=0)
                legal=0;
            if(strcmp("end",temp)==0)
                return -1;
        }
        else
            legal=0;
    }
    if(strcmp("down",direction)==0){
        if(object.location_row+step_num<map.get_size_row())
        for(int count=1;count<=step_num;count++){

            char* temp=map.content[object.location_row+count][object.location_col];
            if(strcmp("grass",temp)!=0)
            if(strcmp("blank",temp)!=0)
                legal=0;
            if(strcmp("end",temp)==0)
                return -1;
        }
        else
            legal=0;
    }
    if(strcmp("left",direction)==0){
        if(object.location_col-step_num>=0)
        for(int count=1;count<=step_num;count++){
            char* temp=map.content[object.location_row][object.location_col-count];
            if(strcmp("grass",temp)!=0)
            if(strcmp("blank",temp)!=0)
                legal=0;
            if(strcmp("end",temp)==0)
                return -1;
        }
        else
            legal=0;
    }
    if(strcmp("right",direction)==0){
        if(object.location_col+step_num<map.get_size_col())
        for(int count=1;count<=step_num;count++){
            char* temp=map.content[object.location_row][object.location_col+count];
            if(strcmp("grass",temp)!=0)
            if(strcmp("blank",temp)!=0)
                legal=0;
            if(strcmp("end",temp)==0)
                return -1;
        }
        else
            legal=0;
    }
    return legal;
}
