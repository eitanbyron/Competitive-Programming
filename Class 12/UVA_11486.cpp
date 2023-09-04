#include <iostream>
#include "vector"
#include "cmath"
#include "numeric"
using namespace std;
typedef vector<long long> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
int mod=1000000007;
int findNumFriends(int bitmap){
    int friends=0;
    for(int digit=0;digit<7;digit++){
        if(bitmap%2==1){
            friends++;
        }
        bitmap/=2;
    }
    return friends;
}
vi numToVec(int bitmap){
    vi res(7,false);
    for(int digit=0;digit<7;digit++){
        if(bitmap%2==1){
           res[digit]=true;
        }
        bitmap/=2;
    }
    return res;
}
int canGo(vi current,vi next){
    vi later;
    if(current[0]){
        if(!next[1]) return false;
        next[1]= false;
    }
    for(int digit=1;digit<6;digit++){
        if(current[digit]){
            int right=digit+1;
            int left=digit-1;
            if(!next[left]&&!next[right]) return false;
            if(next[left]&&next[right]) later.push_back(digit);
            else{
                next[left]=next[right]= false;
            }

        }
    }
    if(current[6]){
        if(!next[5]) return false;
        next[5]= false;
    }
    for(int i : later){
        if(!next[i-1]&&!next[i+1]) return false;
        if(!(next[i-1]&&next[i+1]))next[i-1]=next[i+1]= false;
    }
    return true;
}
vvi multiply(vvi& A, vvi& B) {
    int n = A.size(), m = A[0].size(), k = B[0].size();
    vvi C(n, vi(k, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < k; j++)
            for(int l = 0; l < m; l++) {
                C[i][j] += A[i][l] * B[l][j];
                C[i][j]%=mod;
            }
    return C;
}
vvi power(vvi& A, long long k) {
    int n = A.size();
    vvi ret(n, vi(n)), B = A;
    for(int i = 0; i < n; i++) ret[i][i]=1;
    while(k) {
        if(k & 1) ret = multiply(ret, B);
        k >>= 1; B = multiply(B, B);
    }
    return ret;
}
vi multiplyVec(vvi& a,vi& b){
    vi c(b.size(),0);
    //a[i].size==b.size
    for(int i=0;i<a.size();i++){
        for(int j=0;j<a[i].size();j++){
            c[i]=(c[i]+(a[i][j]* b[j]))%mod;
        }
    }
    return c;
}
int main() {
    int tests;
    cin>>tests;
    vvi legalVector;
    for(int bitmap=0;bitmap<pow(2,7);bitmap++){
        if(findNumFriends(bitmap)==4) legalVector.push_back(numToVec(bitmap));
    }
    vvi a(35,vi(35));
    for(int i=0;i<35;i++){
        for(int j=0;j<35;j++){
            a[i][j]= canGo(legalVector[i],legalVector[j]);
        }
    }
    long long n;
    vi startingPos(7);
    vvi ans;
    for(int i=0;i<tests;i++){
        startingPos=vi(7,0);
        cin>>n;
        for(int j=0;j<7;j++){
            int temp;
            cin>>temp;
            if(temp!=0) startingPos[j]=1;
        }
        ans=power(a,n-1);
        /*for(int l=0;l<ans.size();l++){
            for(int m=0;m<ans[l].size();m++){
                cout<<ans[l][m]<<" ";
            }
            cout<<endl;

        }*/
        int startIndex=-1;
        for(int j=0;j<35;j++){
            if(startingPos==legalVector[j]){
                startIndex=j;
                //cout<<"starting pose: "<<j<<endl;
                break;
            }
        }
        vi startVec(35,0);
        startVec[startIndex]=1;

        vi final=multiplyVec(ans,startVec);
        long long res=0;
        for(int j=0;j<final.size();j++){
            res+=final[j];
            res%=mod;
        }
        cout<<res<<endl;
    }

    return 0;
}
