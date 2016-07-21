#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <ctime>
using namespace std;

void SetColor(int front=7, int back=0){
    int color=front+16*back;
    HANDLE stdHandle=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(stdHandle,color);
}

void SetCursorVisible(bool visibility){
    CONSOLE_CURSOR_INFO cursor;
    HANDLE stdHandle;
    stdHandle=GetStdHandle(STD_OUTPUT_HANDLE);
    cursor.bVisible=visibility;
    cursor.dwSize=100;
    SetConsoleCursorInfo(stdHandle,&cursor);

}

class LETTER{
    private:
        int row;
        int col;
        char letter;
    public:
        void input(char iletter);
        void displace(int irow, int icol);
        void go(int irow, int icol);
        void print();
        LETTER(char iletter,int irow, int icol);
        LETTER();
        ~LETTER();
        void clean();
        void cgo(int icol);
};

void gotorc(int row, int col);

void LETTER::input(char iletter){
    letter=iletter;
}

void LETTER::displace(int irow,int icol){
    row+=irow;
    col+=icol;
    gotorc(row,col);
}

void LETTER::go(int irow, int icol){
    row=irow;
    col=icol;
    gotorc(row,col);
}

void LETTER::cgo(int icol){
    col=icol;
    gotorc(row,col);
}
int picked[]={2,4,6};
void LETTER::print(){
    switch(letter){
        case 'A':
            gotorc(row,col);
            puts("    A");gotorc(row+1,col);
            puts("   A A");gotorc(row+2,col);
            puts("  A A A");gotorc(row+3,col);
            puts(" A     A");gotorc(row+4,col);
            puts("A       A");
            break;
        case 'B':
            gotorc(row,col);
            puts("B B B");gotorc(row+1,col);
            puts("B    B");gotorc(row+2,col);
            puts("B B B");gotorc(row+3,col);
            puts("B    B");gotorc(row+4,col);
            puts("B B B");
            break;
        case 'C':
            gotorc(row,col);
            puts(" C C C");gotorc(row+1,col);
            puts("C");gotorc(row+2,col);
            puts("C");gotorc(row+3,col);
            puts("C     C");gotorc(row+4,col);
            puts(" C C C");
            break;
        case 'D':
            gotorc(row,col);
            puts("D D D");gotorc(row+1,col);
            puts("D    D");gotorc(row+2,col);
            puts("D     D");gotorc(row+3,col);
            puts("D    D");gotorc(row+4,col);
            puts("D D D");
            break;
        case 'E':
            gotorc(row,col);
            puts("E E E");gotorc(row+1,col);
            puts("E");gotorc(row+2,col);
            puts("E E E");gotorc(row+3,col);
            puts("E");gotorc(row+4,col);
            puts("E E E");
            break;
        case 'F':
            gotorc(row,col);
            puts("F F F");gotorc(row+1,col);
            puts("F");gotorc(row+2,col);
            puts("F F F");gotorc(row+3,col);
            puts("F");gotorc(row+4,col);
            puts("F");
            break;
        case 'G':
            gotorc(row,col);
            puts(" G G G");gotorc(row+1,col);
            puts("G");gotorc(row+2,col);
            puts("G   G G");gotorc(row+3,col);
            puts("G     G");gotorc(row+4,col);
            puts(" G G G");
            break;
        case 'H':
            gotorc(row,col);
            puts("H     H");gotorc(row+1,col);
            puts("H     H");gotorc(row+2,col);
            puts("H H H H");gotorc(row+3,col);
            puts("H     H");gotorc(row+4,col);
            puts("H     H");
            break;
        case 'I':
            gotorc(row,col);
            puts("I I I I I");gotorc(row+1,col);
            puts("    I");gotorc(row+2,col);
            puts("    I");gotorc(row+3,col);
            puts("    I");gotorc(row+4,col);
            puts("I I I I I");
            break;
        case 'J':
            gotorc(row,col);
            puts(" J J J");gotorc(row+1,col);
            puts("   J");gotorc(row+2,col);
            puts("   J");gotorc(row+3,col);
            puts("J  J");gotorc(row+4,col);
            puts(" J J");
            break;
        case 'K':
            gotorc(row,col);
            puts("K   K");gotorc(row+1,col);
            puts("K  K");gotorc(row+2,col);
            puts("K K");gotorc(row+3,col);
            puts("K  K");gotorc(row+4,col);
            puts("K   K");
            break;
        case 'L':
            gotorc(row,col);
            puts("L");gotorc(row+1,col);
            puts("L");gotorc(row+2,col);
            puts("L");gotorc(row+3,col);
            puts("L   L");gotorc(row+4,col);
            puts("L L L");
            break;
        case 'M':
            gotorc(row,col);
            puts("M M   M M");gotorc(row+1,col);
            puts("M  M M  M");gotorc(row+2,col);
            puts("M   M   M");gotorc(row+3,col);
            puts("M       M");gotorc(row+4,col);
            puts("M       M");
            break;
        case 'N':
            gotorc(row,col);
            puts("N     N");gotorc(row+1,col);
            puts("N N   N");gotorc(row+2,col);
            puts("N  N  N");gotorc(row+3,col);
            puts("N   N N");gotorc(row+4,col);
            puts("N     N");
            break;
        case 'O':
            gotorc(row,col);
            puts(" O O O");gotorc(row+1,col);
            puts("O     O");gotorc(row+2,col);
            puts("O     O");gotorc(row+3,col);
            puts("O     O");gotorc(row+4,col);
            puts(" O O O");
            break;
        case 'P':
            gotorc(row,col);
            puts("P P P");gotorc(row+1,col);
            puts("P    P");gotorc(row+2,col);
            puts("P P P");gotorc(row+3,col);
            puts("P");gotorc(row+4,col);
            puts("P");
            break;
        case 'Q':
            gotorc(row,col);
            puts(" Q Q Q");gotorc(row+1,col);
            puts("Q     Q");gotorc(row+2,col);
            puts("Q   Q Q");gotorc(row+3,col);
            puts("Q    QQ");gotorc(row+4,col);
            puts(" Q Q Q Q");
            break;
        case 'R':
            gotorc(row,col);
            puts("R R R");gotorc(row+1,col);
            puts("R    R");gotorc(row+2,col);
            puts("R R R");gotorc(row+3,col);
            puts("R    R");gotorc(row+4,col);
            puts("R     R");
            break;
        case 'S':
            gotorc(row,col);
            puts("S S S");gotorc(row+1,col);
            puts("S");gotorc(row+2,col);
            puts("S S S");gotorc(row+3,col);
            puts("    S");gotorc(row+4,col);
            puts("S S S");
            break;
        case 'T':
            gotorc(row,col);
            puts("T T T T T");gotorc(row+1,col);
            puts("    T");gotorc(row+2,col);
            puts("    T");gotorc(row+3,col);
            puts("    T");gotorc(row+4,col);
            puts("    T");
            break;
        case 'U':
            gotorc(row,col);
            puts("U     U");gotorc(row+1,col);
            puts("U     U");gotorc(row+2,col);
            puts("U     U");gotorc(row+3,col);
            puts("U     U");gotorc(row+4,col);
            puts(" U U U");
            break;
        case 'V':
            gotorc(row,col);
            puts("V     V");gotorc(row+1,col);
            puts("V     V");gotorc(row+2,col);
            puts(" V   V");gotorc(row+3,col);
            puts("  V V");gotorc(row+4,col);
            puts("   V");
            break;
        case 'W':
            gotorc(row,col);
            puts("W     W");gotorc(row+1,col);
            puts("W  W  W");gotorc(row+2,col);
            puts("W  W  W");gotorc(row+3,col);
            puts(" W W W");gotorc(row+4,col);
            puts("  W W");
            break;
        case 'X':
            gotorc(row,col);
            puts("X   X");gotorc(row+1,col);
            puts(" X X");gotorc(row+2,col);
            puts("  X");gotorc(row+3,col);
            puts(" X X");gotorc(row+4,col);
            puts("X   X");
            break;
        case 'Y':
            gotorc(row,col);
            puts("Y   Y");gotorc(row+1,col);
            puts(" Y Y");gotorc(row+2,col);
            puts("  Y");gotorc(row+3,col);
            puts("  Y");gotorc(row+4,col);
            puts("  Y");
            break;
        case 'Z':
            gotorc(row,col);
            puts("Z Z Z");gotorc(row+1,col);
            puts("   Z");gotorc(row+2,col);
            puts("  Z");gotorc(row+3,col);
            puts(" Z");gotorc(row+4,col);
            puts("Z Z Z");
            break;
        case ' ':
            SetColor();
            gotorc(row,col);
            puts("          ");gotorc(row+1,col);
            puts("          ");gotorc(row+2,col);
            puts("          ");gotorc(row+3,col);
            puts("          ");gotorc(row+4,col);
            puts("          ");
            break;
        case '!':
            gotorc(row,col);
            puts("  ! ! !");gotorc(row+1,col);
            puts("  ! ! !");gotorc(row+2,col);
            puts("    !");gotorc(row+3,col);
            puts("    ");gotorc(row+4,col);
            puts("    !");
            break;
        case '\n':
            go(row+10,0);
            break;
    }

}

LETTER::LETTER(char iletter, int irow, int icol){
    input(iletter);
    go(irow,icol);
}

LETTER::~LETTER(){
}

LETTER::LETTER(){
    input('\0');
    go(0,0);
}

void LETTER::clean(){
    char temp=letter;
    input(' ');
    print();
    input(temp);
}

void gotorc(int row, int col){
    COORD screen;
    HANDLE output;
    output=GetStdHandle(STD_OUTPUT_HANDLE);
    screen.X=col;
    screen.Y=row;
    SetConsoleCursorPosition(output,screen);
}



int main(){
    srand(time(NULL));
    SetCursorVisible(false);
    char temp;
    char input[100]="THIS\nIS\nMACUREE!!!";
    system("cls");
    while(1){
        LETTER a;
        int line=0;
        for(int count=0;input[count]!='\0';count++){
            if(input[count]=='\n'){
                a.input('\n');
                a.print();
                line=0;
            }
            else{
                line++;
                a.input(input[count]);
                if(line==11){
                    a.displace(10,0);
                    line=1;
                }
                int clr=picked[rand()%3];
                for(int count2=0;count2<=11-line;count2++){
                    SetColor(clr);
                    a.cgo(100-10*count2);
                    a.print();
                    Sleep(50);
                    if(count2!=11-line)
                        a.clean();

                }
            }
        }
        Sleep(2000);
        system("cls");
        gotorc(1,1);
    }
    SetColor();
    return 0;
}
