#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;


vector<pair<double, double>> points;
set<pair<double, double>> y_set;



int main() {
    int n,last_point;
    double x,y;
    cin >> n;
    while (n > 0)
    {
        last_point=0;
        y_set.clear();
        points.assign(n, {0,0});
        for (int i =0; i<n;i++)
        {
            cin >> x >>y;
            points[i] = {x,y};
        }
        sort(points.begin(),points.end());
        double ans = 1e12;
        pair<pair<double, double>, pair<double, double>> ans_pair;
        for (int i=0; i<n; i++){
            while (last_point < i && points[i].first - points[last_point].first >= ans){
                y_set.erase({points[last_point].second, points[last_point].first});
                last_point++;
            }

            auto lo_it = y_set.lower_bound({points[i].second - ans, -100005});
            auto hi_it = y_set.upper_bound({points[i].second + ans, 100005});

            for (auto it = lo_it; it != hi_it; it++){
                double d = hypot(points[i].first-it->second,points[i].second-it->first);
                if (ans > d){
                    ans = d;
                    ans_pair = {points[i], {it->second, it->first}};
                }
            }
            y_set.insert({points[i].second, points[i].first});
        }
        cin>>n;
        if (ans < 10000)
            cout << fixed << setprecision(4) <<  ans << endl;
        else
            cout << "INFINITY" << endl;
    }
    return 0;
}