#include <bits/stdc++.h>

using namespace std;

struct IndexCor{
    int row;
    int col;
    int index;
    IndexCor(int row, int col, int index):
        row(row),col(col),index(index){}
    friend bool operator<(IndexCor const& left, IndexCor const& right){
        return left.index<right.index;
    }
};

int main(){
    bool cont = true;
    srand(time(NULL));
    while(cont){
        printf("This is Random Seating System\n");
        printf("Input the size of your class room:\n");
        printf("It must be a pair of positive integers \"n m\"\n");
        cont = false;
        int n,m;
        cin>>n>>m;
        int seats[n][m];
        memset(seats,-1,sizeof(seats));
        set<IndexCor> spec;
        set<pair<int,int> > preArranged;
        vector<IndexCor> unspec;
        printf("Specify the index of seat you would like to fix:\n");
        printf("It must be in the form of \"r c i\",\n");
        printf("\"r c\" stands for the row and column of the seat\n");
        printf("\"i\" stands for the index of the seat\n");
        printf("End the input serial with \"0 0 0\"\n");
        while(1){
            int r,c,i;
            cin>>r>>c>>i;
            if(!r&&!c&&!i) break;
            r--,c--;
            spec.insert(IndexCor(r,c,i));
            preArranged.insert(pair<int,int>(r,c));
        }
        printf("Enter the number of sitting people:\n");
        int people;
        cin>>people;
        int ind = 1;
        for(int row=0;row<n;row++)
        for(int col=0;col<m;col++){
            if(spec.count(IndexCor(row,col,ind))){
                ind++;
                col--;
                continue;
            }
            if(preArranged.count(pair<int,int>(row,col)))
                continue;
            if(unspec.size()+spec.size()>=people) break;
            unspec.push_back(IndexCor(row,col,ind++));
        }
        for(int cnt=0;cnt<unspec.size();cnt++)
            swap(unspec[cnt].index,unspec[rand()%unspec.size()].index);
        for(int cnt=0;cnt<unspec.size();cnt++)
            seats[unspec[cnt].row][unspec[cnt].col] = unspec[cnt].index;
        set<IndexCor>::iterator end = spec.end();
        for(set<IndexCor>::iterator i = spec.begin();i!=end;++i){
            seats[i->row][i->col] = i->index;
        }
        for(int row=0;row<n;row++){
            for(int col=0;col<m;col++)
                printf("%5d ",seats[row][col]);
            printf("\n");
        }
        printf("\n");
        printf("Continue?(y/n)\n");
        while(1){
            int temp = getchar();
            if('a'<=temp&&temp<='z'){
                if(temp=='y') cont=true;
                break;
            }
        }
        if(cont) printf("\n");
    }
}

