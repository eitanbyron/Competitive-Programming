#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

#define EPS 1e-9

int main() {
    int n,minute;
    double profit;
    vector<double> timeline;
    cin >> n;
    while (n != 0) {
        double sum = 0, max = 0;
        int sum_start = 0, sum_duration = 0, max_start = 0, max_duration = 0;
        timeline.assign(1440, -0.08);
        for (int i = 0; i < n; i++) {
            cin >> minute >> profit;
            timeline[minute] += profit;
        }
        for (int i = 0; i < 1440; i++) {
            sum += timeline[i];
            if (sum > EPS) {
                sum_duration++;
            } else {
                sum = 0;
                sum_start = i + 1;
                sum_duration = 0;
            }
            if (sum - max > EPS) {
                max = sum;
                max_start = sum_start;
                max_duration = sum_duration;
            } else if (abs(max - sum) <= EPS) {
                if (sum_duration < max_duration) {
                    max_start = sum_start;
                    max_duration = sum_duration;
                }
            }
        }
        if (abs(0 - max) > EPS) {
            cout << fixed << setprecision(2) << max << " " << max_start << " " << max_start + max_duration -1 << endl;
        } else {
            cout << "no profit" << endl;
        }
        cin >> n;
    }
    return 0;
}