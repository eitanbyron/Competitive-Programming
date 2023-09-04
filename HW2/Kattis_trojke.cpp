#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include <random>
using namespace std;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
int choose3(int n){
    return (n*(n-1)*(n-2))/6;
}
int main() {
    int n;
    cin>>n;
    vector<ii> points;
    char letter;
    for(int row=0;row<n;row++){
        for(int col=0;col<n;col++){
            cin>>letter;
            if(letter!='.'){
                points.emplace_back(row,col);
            }
        }
    }
    //auto rng = default_random_engine {};
    //std::shuffle(std::begin(points), std::end(points), rng);
    int sum=0;
    vvb table(points.size(),vb(points.size(), false));
    vi sameLineIdx;
    for(int i=0;i<points.size();i++){
        ii main=points[i];
        for(int j=i;j<points.size();j++){
            if(i==j || table[i][j]) continue;
            ii line=ii(points[j].first-main.first,points[j].second-main.second);
            for(int k=j;k<points.size();k++){
                if(i==k||j==k || table[i][k] ||table[j][k]) continue;
                if(line.first==0){
                    if(points[k].first==main.first) sameLineIdx.push_back(k);
                } else{
                    if(line.second*(points[k].first-main.first)==line.first*(points[k].second-main.second)) {
                        sameLineIdx.push_back(k);
                    }
                }
            }
            sameLineIdx.push_back(i);
            sameLineIdx.push_back(j);
            if(sameLineIdx.size()>2)sum+= choose3(sameLineIdx.size());
            for(int p1=0;p1<sameLineIdx.size();p1++){
                for(int p2=0;p2<sameLineIdx.size();p2++){
                    table[sameLineIdx[p1]][sameLineIdx[p2]]= true;
                }
            }
            sameLineIdx.clear();
        }
    }
    cout<<sum<<endl;
    return 0;
}
