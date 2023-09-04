#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#define place dp[candiesNum[0]][candiesNum[1]][candiesNum[2]][candiesNum[3]]
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;
int recursion(const vvi& pipes,vi& basket,vi& candiesNum,vvvvi& dp){
    if(place!=-1) return place;
    if(basket[0]==5) return 0;
    int pairs;
    int maxSum=0;

    for(int i=0;i<4;i++){
        if(candiesNum[i]==0) continue;
        pairs=0;
        vi nBasket=basket;
        candiesNum[i]--;
        nBasket[pipes[i][candiesNum[i]]]++;
        nBasket[0]++;
        if(nBasket[pipes[i][candiesNum[i]]]==2){
            pairs=1;
            nBasket[0]-=2;
            nBasket[pipes[i][candiesNum[i]]]-=2;
        }
        if(recursion(pipes,nBasket,candiesNum,dp)+pairs>maxSum) maxSum=recursion(pipes,nBasket,candiesNum,dp)+pairs;
        candiesNum[i]++;
    }
    place=maxSum;
    return maxSum;
}
int main() {
    int n;
    cin>>n;
    vvi pipes(4);
    vi candiesIdx(4);
    vi basket;
    while(n!=0){
        basket=vi(21,0);
        pipes=vvi(4);
        candiesIdx=vi(4,n);
        vvvvi dp(n+1,vvvi(n+1,vvi(n+1,vi(n+1,-1))));

        for(int i=0;i<n;i++){
            int x1,x2,x3,x4;
            cin>>x1>>x2>>x3>>x4;
            pipes[0].push_back(x1);
            pipes[1].push_back(x2);
            pipes[2].push_back(x3);
            pipes[3].push_back(x4);
        }
        for(int i=0;i<4;i++){
            reverse(pipes[i].begin(),pipes[i].end());
        }

        cout<<recursion(pipes,basket,candiesIdx,dp)<<endl;
        cin>>n;
    }
    return 0;
}
