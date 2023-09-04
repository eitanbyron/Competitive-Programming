#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include <algorithm>


using namespace std;
vector<pair<int,int>> v;

double check (double time)
{
    double maxi = -1e6, mini =1e6;
    for (auto p: v)
    {
        double a= p.first, b= p.second;
        double location = a + b*time;
        maxi = max(maxi,location);
        mini = min(mini,location);
    }
    return maxi -mini;
}

int main() {
    int n;
    double midl,midh,high = 1e6, low =0;
    pair<int,int> temp;
    cin >> n;
    for (int i = 0; i< n; i++)
    {
        cin>>temp.first;
        cin>>temp.second;
        v.push_back(temp);
    }
    for (int i =0; i<100; i++)
    {
        midl= low + (high -low)/3;
        midh = high - (high -low)/3;

        if (check(midl) < check(midh))
            high = midh;
        else
            low = midl;
    }

    cout << fixed << setprecision(5) << check(high) << endl;
    return 0;
}