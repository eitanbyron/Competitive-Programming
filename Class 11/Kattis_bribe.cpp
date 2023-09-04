#include <iostream>
#include "vector"
#include "map"
#include "cmath"
#include "algorithm"
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<vvd> vvvd;
int c,n;
double solve(int bitmap,int x ,const vb& valid,const vd& probs,vvd& dp){
    if(dp[bitmap][x]!=-1) return dp[bitmap][x];
    if(!valid[bitmap]) {
        dp[bitmap][x]=0;
        return 0;
    }
    if(x>=c) {
        dp[bitmap][x]=1;
        return 1;
    }
    double best=0;
    for(int i=0;i<n;i++){
        if(((bitmap>>i)&1)!=1) best=max(best,solve(bitmap|(1<<i),x+1,valid,probs,dp)*probs[i]+ solve(bitmap|(1<<i),x,valid,probs,dp)*(1-probs[i]));
    }
    dp[bitmap][x]=best;
    return best;
}
int sum(vi mount,int bm){
    int sum=0;
    for(int i=0;i<mount.size();i++){
        if(((bm>>i)&1)==1) sum+=mount[i];
    }
    return sum;
}
int main() {
    int tests;
    cin>>tests;
    for(int h=0;h<tests;h++){
        int m;
        cin>>n>>c>>m;
        vi bribeMount(n);
        vd bribeProb(n);
        for(int i=0;i<n;i++){
            cin>>bribeMount[i]>>bribeProb[i];
            bribeProb[i]/=100;
        }

        //calculate the valid bitmaps
        vb valid(pow(2,n), false);
        vvd dp(pow(2,n),vd(c+1,-1));
        for(int bm=0;bm<valid.size();bm++){
            if(sum(bribeMount,bm)<=m) valid[bm]=true;
        }
        //dp
        cout<<solve(0,0,valid,bribeProb,dp)<<endl;


    }
    return 0;
}
