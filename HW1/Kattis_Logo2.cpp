#include <iostream>
#include <math.h>
#include <vector>
#include <bitset>
#include <cstring>
using namespace std;



#define EPS 1e-8

using namespace std;
typedef long double ld;


#define INF 1e9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point { double x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
    bool operator < (point other) const { // override less than operator
        if (fabs(x - other.x) > EPS)                 // useful for sorting
            return x < other.x;          // first criteria , by x-coordinate
        return y < other.y; }          // second criteria, by y-coordinate
    // use EPS (1e-9) when testing equality of two floating points
    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); } };




struct vec {
    ld x, y;
    vec(ld _x, ld _y) : x(_x), y(_y) {}
    vec(point p1, point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}

    vec operator+(const vec &v) const { return vec(x + v.x, y + v.y); }
    vec operator-(const vec &v) const { return vec(x - v.x, y - v.y); }
    vec operator*(const ld &r) const { return vec(x * r, y * r); }
    vec operator/(const ld &r) const { return vec(x / r, y / r); }

    ld length() { return hypot(x, y); }


    ld length_sq() { return x * x + y * y; }
};


vec rotate(ld rad, vec v) {
    ld x = v.x;
    ld y = v.y;
    ld nx = x * cos(rad) - y * sin(rad);
    ld ny = x * sin(rad) + y * cos(rad);
    return vec(nx, ny);
}



int query_type = 0;
vector<vector<int>> commands;

int main() {
    int t, n, unknown;
    char cmd[10];
    char units[10];
    cin >> t;

    while (t--) {
        cin >> n;
        commands.assign(1005, vector<int> (2,0));
        for (int i = 0; i < n; i++) {
            cin>>cmd;
            if (::strcmp(cmd, "fd") == 0)
                commands[i][0] = 1;
            if (::strcmp(cmd, "lt") == 0)
                commands[i][0] = 3;
            if (::strcmp(cmd, "rt") == 0)
                commands[i][0] = 4;
            if (::strcmp(cmd, "bk") == 0)
                commands[i][0] = 2;
            cin >>cmd;
            if (::strcmp(cmd, "?") == 0) {
                unknown = i;
                query_type = commands[i][0];
            }
            else
                commands[i][1] = ::atoi(cmd);
        }

        if (query_type == 1 || query_type == 2) {
            vec direction = vec(point(0, 0), point(0, 1));  // toward positive y
            vec cur_vec = vec(point(0, 0), point(0, 0));
            for (int index = 0; index < n; index++) {
                if (index == unknown) {
                    continue;
                }
                if (commands[index][0] == 3) {
                    direction = rotate(DEG_to_RAD(commands[index][1] % 360), direction);
                    direction = direction / direction.length();
                } else if (commands[index][0] == 4) {
                    direction =
                            rotate(DEG_to_RAD(-commands[index][1] % 360), direction);
                    direction = direction / direction.length();
                } else if (commands[index][0] == 1) {
                    cur_vec = cur_vec + direction * commands[index][1];
                } else if (commands[index][0] == 2) {
                    cur_vec = cur_vec - direction * commands[index][1];
                }
            }
            cout << int(roundl(cur_vec.length())) << endl;

        } else {
            for (int theta = 0; theta < 360; theta++) {
                vec direction = vec(point(0, 0), point(0, 1));
                vec cur_vec = vec(point(0, 0), point(0, 0));
                for (int index = 0; index < n; index++) {
                    if (index == unknown) {
                        if (commands[index][0] == 3) {
                            direction = rotate(DEG_to_RAD(theta), direction);
                            direction = direction / direction.length();
                        } else if (commands[index][0] == 4) {
                            direction = rotate(DEG_to_RAD(360 - theta), direction);
                            direction = direction / direction.length();
                        }
                        continue;
                    }

                    if (commands[index][0] == 3) {
                        direction =
                                rotate(DEG_to_RAD(commands[index][1] % 360), direction);
                        direction = direction / direction.length();
                    } else if (commands[index][0] == 4) {
                        direction =
                                rotate(DEG_to_RAD(-commands[index][1] % 360), direction);
                        direction = direction / direction.length();
                    } else if (commands[index][0] == 1) {
                        cur_vec = cur_vec + direction * commands[index][1];
                    } else if (commands[index][0] == 2) {
                        cur_vec = cur_vec - direction * commands[index][1];
                    }
                }
                if (fabs(cur_vec.x) < EPS && fabs(cur_vec.y) < EPS) {
                    cout << theta << endl;
                    break;
                }
            }
        }
    }

    return 0;
}