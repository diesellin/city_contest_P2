#include<bits/stdc++.h>
using namespace std;
int N,M,Q;
vector<int>e[100005];
int id[100005][102];
int c[1000005]={};
//queue
int st=0,sz=0;
int d[100005],ma[100005],p[100005];
void add(int dd,int mm,int pp){
    d[sz]=dd;
    ma[sz]=mm;
    p[sz]=pp;
    sz++;
}
int hg[128][100005]={};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M>>Q;
    int mxid=N;
    for(int i=1;i<=N;i++){
        id[i][0]=i;
        for(int j=1;j<102;j++){
            id[i][j]=++mxid;
            e[id[i][j-1]].push_back(id[i][j]);
        }
    }
    while(M--){
        int a,b,w;
        cin>>a>>b>>w;
        e[id[a][w-1]].push_back(b);
    }
    while(Q--){
        int a,d,co;
        cin>>a>>d>>co;
        c[id[a][d]]|=(1<<co);
    }
    add(0,c[1],1);
    int ans=2e9,cnt=0;
    while(st<sz){
        int dis=d[st],mask=ma[st],x=p[st];
        st++;
        if(hg[mask][x] || dis>ans){
            continue;
        }
        hg[mask][x]=1;
        if(x==N){
            ans=min(ans,dis);
            int ccnt=0;
            for(int i=0;i<7;i++){
                if(mask&(1<<i)){
                    ccnt++;
                }
            }
            cnt=max(cnt,ccnt);
        }
        for(int y:e[x]){
            add(dis+1,mask|c[y],y);
        }
    }
    if(ans==2e9){
        cout<<"-1 -1";
    }else{
        cout<<ans<<" "<<cnt;
    }  
}
