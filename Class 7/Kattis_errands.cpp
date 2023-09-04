//
// Created by barbe on 26/05/2023.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
using namespace std;
const double EPS = 1e-12;
struct Point {
    double x, y;
};
int n;
map<string, Point> locations;
vector<Point> testCaseLocations;
vector<int> orderVisits;
vector<string> reverseMapper;
vector<vector<double>> memo;

double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double dp(int u, int bm) {
    if (bm == 0) {
        return distance(locations["home"], testCaseLocations[u]);
    }
    double& ans = memo[u][bm];
    if (ans != -1) {
        return ans;
    }
    ans = 1e9;
    int m = bm;
    while (m) {
        int twoPowV = m & -m;
        int v = __builtin_ctz(twoPowV) + 1;
        ans = min(ans, distance(testCaseLocations[u], testCaseLocations[v]) + dp(v, bm ^ twoPowV));
        m -= twoPowV;
    }
    return ans;
}

void fillOrderVisits(int u, int bm) {
    if (bm == 0) {
        return;
    }
    int m = bm;
    while (m) {
        int twoPowV = m & -m;
        int v = __builtin_ctz(twoPowV) + 1;
        m -= twoPowV;

        if (abs(dp(u, bm) - (distance(testCaseLocations[u], testCaseLocations[v]) + dp(v, bm ^ twoPowV))) <= EPS) {
            orderVisits.push_back(v);
            fillOrderVisits(v, bm ^ twoPowV);
            break;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string name;
        Point point{};
        cin >> name >> point.x >> point.y;
        locations[name] = point;
    }
    string testCase;
    while (getline(cin, testCase)) {
        testCaseLocations.clear();
        orderVisits.clear();
        reverseMapper.clear();
        testCaseLocations.push_back(locations["work"]);
        reverseMapper.emplace_back("work");
        istringstream ss(testCase);
        string name;
        while (ss >> name) {
            testCaseLocations.push_back(locations[name]);
            reverseMapper.push_back(name);
        }

        n = testCaseLocations.size();
        memo.assign(n, vector<double>((1 << (n - 1)) + 1, -1));
        fillOrderVisits(0, (1 << (n - 1)) - 1);
        for (int i = 0; i < orderVisits.size(); i++) {
            cout << reverseMapper[orderVisits[i]] << (i == orderVisits.size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

