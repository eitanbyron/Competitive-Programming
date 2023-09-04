#include <iostream>
using namespace std;
int auklid(int a,int b){
    if(a==0||b==0) return a+b;
    return auklid(max(a,b)%min(a,b),min(a,b));
}
int main() {
    int n,k;
    int gcd=360;
    cin>>n>>k;
    int angle;
    for(int i=0;i<n;i++){
        cin>>angle;
        gcd= auklid(gcd,angle);
    }
    for(int i=0;i<k;i++){
        cin>>angle;
        if(angle%gcd==0) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
