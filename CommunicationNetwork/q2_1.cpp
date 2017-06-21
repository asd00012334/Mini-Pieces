#include<bits/stdc++.h>

using namespace std;

inline double prand(){
    double temp = (double)rand()/RAND_MAX;
    if(1-temp<1e-6) return 1-1e-6;
    return temp;
}

inline double poissArrival(double lambda, double delta=1){
    return -log(1-prand())*delta/lambda;
}

inline double serveTime(double v){
    return -log(1-prand())/v;
}

struct BS{
    static const int num = 1e4;
    int idx;
    struct Channel{
        int ch;
        int owner;
        int user;
        double arriveBegin;
        double arriveEnd;
    };
    vector<Channel> chs;
    double lambda;
    double v;
};

int main(){
    srand(time(NULL));
    double lambda = 1;
    double v = 0.2;
    vector<BS> bs(13);
    for(int cnt=1;cnt<=12;cnt++){
        bs[cnt].idx = cnt;
        bs[cnt].lambda = (cnt%4+1)*lambda;
        bs[cnt].v = (cnt%4+1)*v;
        int base = cnt%3*5;
        for(int ch=0;ch<5;ch++){
            BS::Channel temp;
            temp.ch = base+ch;
            temp.owner = cnt;
            temp.user = -1;
            bs[cnt].chs.push_back(temp);
        }
    }
    double base = 0;
    double avgBlock = 0;
    cout<<"Block rate:\n";
    for(int bsIdx=1;bsIdx<=12;bsIdx++){
        BS& curBS = bs[bsIdx];
        double base = 0;
        double totalCnt = 0;
        queue<double> req;
        while(base<1e2){
            base+=poissArrival(curBS.lambda);
            req.push(base);
            totalCnt+=1;
        }
        double block = 0;
        while(req.size()){
            for(int ch=0;ch<curBS.chs.size();ch++){
                BS::Channel& curCh = curBS.chs[ch];
                if(curCh.user!=-1&&curCh.arriveEnd<=req.front()){
                    curCh.user = -1;
                }
                if(curCh.user==-1){
                    /// Empty Channel, can be taken
                    curCh.user = curCh.owner;
                    curCh.arriveBegin = req.front();
                    curCh.arriveEnd = req.front()+serveTime(curBS.v);
                    break;
                } else{
                    if(ch==curBS.chs.size()-1){
                        block+=1;
                        break;
                    }
                }
            }
            req.pop();
        }
        avgBlock += block/totalCnt;
        cout<<"    BS"<<bsIdx<<":"<<block/totalCnt<<endl;
    }
    avgBlock/=12;
    cout<<"Avg Block Rate: "<<avgBlock<<"\n";
    system("pause");
    return 0;
}
