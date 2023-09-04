//
// Created by barbe on 10/06/2023.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class line {
public:
    double x1, y1;
    double x2, y2;
};

pair<double, double> areLinesIntersect (line line1, line line2) {
    double delta_y_1 = line1.y2 - line1.y1;
    double delta_x_1 = line1.x1 - line1.x2;
    double c1 = delta_y_1 * (line1.x1) + delta_x_1 * (line1.y1);
    double delta_y_2 = line2.y2 - line2.y1;
    double delta_x_2 = line2.x1 - line2.x2;
    double c2 = delta_y_2 * (line2.x1) + delta_x_2 * (line2.y1);
    double d = delta_y_1 * delta_x_2 - delta_y_2 * delta_x_1;
    double x = (delta_x_2 * c1 - delta_x_1 * c2) / d;
    double y = (delta_y_1 * c2 - delta_y_2 * c1) / d;

    if ((!((y >= line1.y1 && y <= line1.y2) || (y >= line1.y2 && y <= line1.y1))) || (!((y >= line2.y1 && y <= line2.y2) || (y >= line2.y2 && y <= line2.y1)))) {
        return {-1.0, -1.0};
    }
    else if ((!((x >= line1.x1 && x <= line1.x2) || (x >= line1.x2 && x <= line1.x1))) || (!((x >= line2.x1 && x <= line2.x2) || (x >= line2.x2 && x <= line2.x1)))) {
        return {-1.0, -1.0};
    }
    return {x, y};
}


bool check(line line1, line line2, line line3) {
    pair<double, double> intersect1, intersect2, intersect3;
    intersect1 = areLinesIntersect(line1, line2);
    intersect2 = areLinesIntersect(line2, line3);
    intersect3 = areLinesIntersect(line1, line3);
    if (intersect1 == make_pair(-1.0, -1.0) || intersect2 == make_pair(-1.0, -1.0) || intersect3 == make_pair(-1.0, -1.0)) {
        return false;
    }
    if ((intersect1.first != intersect2.first || intersect1.second != intersect2.second) && (intersect2.first != intersect3.first || intersect2.second != intersect3.second) &&
        (intersect3.first != intersect1.first || intersect3.second != intersect1.second)) {
        return true;
    }
    return false;
}
int main(){
    int n;
    while( cin >> n ) {
        if (n == 0) break;
        vector<line> v;
        for (int i = 0; i < n; ++i) {
            double x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            line line1;
            line1.x1 = x1;
            line1.x2 = x2;
            line1.y1 = y1;
            line1.y2 = y2;
            v.push_back(line1);
        }
        int counter = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    bool isThereTriangle = check(v[i], v[j], v[k]);
                    if (isThereTriangle) {
                        counter++;
                    }
                }
            }
        }

        cout << counter << endl;
    }

    return 0;
}