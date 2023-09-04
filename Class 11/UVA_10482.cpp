#include <iostream>
#include "vector"
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
int main() {
    int tests;
    int n;
    int minDiff;
    cin>>tests;
    for(int t=1;t<=tests;t++){
        minDiff=1000;
        cin>>n;
        vi candies=vi(n);
        for(int i=0;i<n;i++){
            cin>>candies[i];
        }
        vi sumCandies=vi(n);
        sumCandies[0]=candies[0];
        for(int i=1;i<n;i++){
            sumCandies[i]=sumCandies[i-1]+candies[i];

        }
        int maxSum=sumCandies[n-1];
        vvvi legalPartitions=vvvi(n,vvi(maxSum,vi(maxSum,0)));
        //first index - candies.
        //second and third - the sum of the first 2 kids
        legalPartitions[0][0][0]=1;
        int kid3;
        for(int i=0;i<n-1;i++){
            int sum=sumCandies[i];
            for(int kid1=0;kid1<=sum;kid1++){
                for(int kid2=0;kid2<=sum;kid2++){
                    if(legalPartitions[i][kid1][kid2]==0) continue;
                    kid3=sum-kid1-kid2;
                    if(kid3<0) continue;
                    legalPartitions[i+1][kid1+candies[i+1]][kid2]++;
                    legalPartitions[i+1][kid1][kid2+candies[i+1]]++;
                    legalPartitions[i+1][kid1][kid2]++;
                }
            }
        }
        for(int kid1=0;kid1<maxSum;kid1++){
            for(int kid2=0;kid2<maxSum;kid2++){
                if(legalPartitions[n-1][kid1][kid2]==0) continue;
                kid3=maxSum-kid1-kid2;
                if(kid3<0) continue;
                if((max(max(kid1,kid2),kid3)-min(min(kid1,kid2),kid3))<minDiff) minDiff=(max(max(kid1,kid2),kid3)-min(min(kid1,kid2),kid3));
            }
        }
        cout<<"Case "<<t<<": "<<minDiff<<endl;
    }
    return 0;
}
