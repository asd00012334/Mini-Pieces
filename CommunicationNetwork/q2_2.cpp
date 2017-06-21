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
    set<int> usingCh;
    double lambda;
    double v;
};

bool avail(vector<vector<int> >& adjList, vector<BS>& bs,
            int chIdx, int userBsIdx){

    vector<int> seeBsIdx;
    seeBsIdx.push_back(userBsIdx);
    for(int cnt=0;cnt<adjList[userBsIdx].size();cnt++)
        seeBsIdx.push_back(adjList[userBsIdx][cnt]);

    for(int bsIdx=0;bsIdx<seeBsIdx.size();bsIdx++){
        BS& curBS = bs[seeBsIdx[bsIdx]];
        if(curBS.usingCh.count(chIdx)){
            return false;
        }
    }
    return true;
}

int main(){
    vector<vector<int> >adjList = {
        {},
        {2,3,8},
        {1,3,10},
        {1,2,4,5,8,10},
        {3,5,6,8,9},
        {3,4,6,10,12},
        {4,5},
        {8,9},
        {1,3,4,7,9},
        {4,7,8},
        {2,3,5,11,12},
        {10,12},
        {5,10,11}
    };
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
            temp.ch = base+ch+1;
            temp.owner = cnt;
            temp.user = -1;
            bs[cnt].chs.push_back(temp);
        }
    }
    double base = 0;
    set<pair<double,int> > req;
    double totalCnt=0;
    /// Generate Packet
    for(int bsIdx=1;bsIdx<=12;bsIdx++){
        BS& curBS = bs[bsIdx];
        double base = 0;
        while(base<1e2){
            base+=poissArrival(curBS.lambda);
            req.insert(pair<double,int>(base,bsIdx));
            totalCnt+=1;
        }
    }
    int self=0, borrow=0, blockCnt=0;
    double block = 0;
    double totalResp[13] = {};
    double blockResp[13] = {};
    while(req.size()){

        /// request income
        double curTime = req.begin()->first;
        int targetBSIdx = req.begin()->second;
        BS& targetBS = bs[targetBSIdx];
        req.erase(req.begin());
        totalResp[targetBSIdx]+=1;        /// refresh all BS channel status
        for(int bsIdx=1;bsIdx<=12;bsIdx++){
            BS& curBS = bs[bsIdx];
            for(int chIdx=0;chIdx<curBS.chs.size();chIdx++){
                BS::Channel& curCh = curBS.chs[chIdx];
                if(curCh.user!=-1 && curCh.arriveEnd<=curTime){
                    bs[curCh.user].usingCh.erase(curCh.ch);
                    curCh.user = -1;
                }
            }
        }


        /// Take in the service
        ///     Case 1: self sufficient
        bool selfSufficient = false;
        for(int tChIdx=0;tChIdx<targetBS.chs.size();tChIdx++){
            BS::Channel& tCh = targetBS.chs[tChIdx];
            if(tCh.user==-1 && avail(adjList,bs,tCh.ch,targetBSIdx)){
                tCh.user = targetBSIdx;
                tCh.arriveBegin = curTime;
                tCh.arriveEnd = curTime + serveTime(targetBS.v);
                bs[tCh.user].usingCh.insert(tCh.ch);
                selfSufficient = true;
                self++;
                break;
            }
        }
        if(selfSufficient) continue;


        ///     Case 2: borrow
        bool brwSufficient = false;
        vector<pair<int,int> >rich;/// <how poor, bs idx>
        for(int cnt=0;cnt<adjList[targetBSIdx].size();cnt++){
            int nBsIdx = adjList[targetBSIdx][cnt];
            BS& nBs = bs[nBsIdx];
            rich.push_back(pair<int,int>(nBs.usingCh.size(),nBsIdx));
        }
        sort(rich.begin(),rich.end());
        for(int nBsIdxIdx=0;nBsIdxIdx<rich.size();nBsIdxIdx++){
            int nBsIdx = rich[nBsIdxIdx].second;
            BS& nBs = bs[nBsIdx];
            for(int cnt=0;cnt<nBs.chs.size();cnt++){
                BS::Channel& brwCh = nBs.chs[cnt];
                if(brwCh.user==-1 && avail(adjList,bs,brwCh.ch,targetBSIdx)){
                    brwSufficient = true;
                    brwCh.user=targetBSIdx;
                    bs[brwCh.user].usingCh.insert(brwCh.ch);
                    brwCh.arriveBegin = curTime;
                    brwCh.arriveEnd = curTime+serveTime(targetBS.v);
                    borrow++;
                    break;
                }
            }
            if(brwSufficient) break;
        }
        if(brwSufficient) continue;

        ///     Case 3: block
        block+=1;
        blockResp[targetBSIdx]+=1;
        blockCnt++;
    }
    block/=totalCnt;
    cout<<"Total: "<<totalCnt<<"\n";
    printf("No borrow: %d\nBorrow: %d\nBlock: %d\n",self,borrow,blockCnt);
    cout<<"Avg block rate: "<<block<<endl;
    for(int cnt=1;cnt<=12;cnt++)
        cout<<"    BS"<<cnt<<": "<<blockResp[cnt]/totalResp[cnt]<<"\n";
    system("pause");
    return 0;
}
