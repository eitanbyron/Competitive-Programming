#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> memo;
vector<int> weights;

int dp(int index, int w){
    if (index == n)
        return abs(1000 - w);
    int &ans = memo[index][w];
    if (ans != -1)
        return ans;
    if (w + weights[index] >= 2001)
        return ans = dp(index+1, w);
    return ans = min(dp(index+1, w+weights[index]), dp(index+1, w));
}

int answer(int index, int w){
    if (index == n) return 0;

    if (dp(index+1, w+weights[index]) != dp(index, w)){
        return answer(index+1, w);
    }
    else{
        return (weights[index] +answer(index+1, w+weights[index]));
    }
}


int main() {
    int temp;
    memo.assign(1001, vector<int> (2001, -1));
    cin >> n;
    for(int i=0; i<n;i++)
    {
        cin >> temp;
        weights.push_back(temp);
    }
    cout << answer(0,0)<<endl;
    return 0;
}