#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <chrono>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <iomanip>
using namespace std;


#define EPS 1e-9


using namespace std;

#define INF 1e9
#define EPS 1e-9


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

double dist(point p1, point p2) {                // Euclidean distance
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(p1.x - p2.x, p1.y - p2.y); }           // return double



struct vec { double x, y;  // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
    return vec(b.x - a.x, b.y - a.y); }

vec scale(vec v, double s) {        // nonnegative s = [<1 .. 1 .. >1]
    return vec(v.x * s, v.y * s); }               // shorter.same.longer

point translate(point p, vec v) {        // translate p according to v
    return point(p.x + v.x , p.y + v.y); }


double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c) {
    // formula: c = a + u * ab
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));                  // translate a to c
    return dist(p, c); }           // Euclidean distance between p and c




int main() {
    int N;
    double x,y, ans= INF, max = 0, dist;
    point a,b,c, check;
    cin >> N;
    vector<point> points(N);
    for (int i =0; i< N; i++)
    {
        cin >> x>>y;
        points[i] = point(x,y);
    }
    for (int i =0; i< N; i++)
    {
        a= points[i], b = points[(i+1) %N];
        max =0;
        for (int j = i+2; j<N +i; j++)
        {
            check = points[j%N];
            dist = distToLine(check, a,b,c);
            if (dist > max)
                max = dist;
        }
        if (max < ans)
            ans = max;
    }
    cout << fixed << setprecision(8) << ans << endl;
    return 0;
}