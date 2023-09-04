#include <iostream>
#include <math.h>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

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

// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) { c = point(a.x, a.y);                   // closer to a
        return dist(p, a); }         // Euclidean distance between p and a
    if (u > 1.0) { c = point(b.x, b.y);                   // closer to b
        return dist(p, b); }         // Euclidean distance between p and b
    return distToLine(p, a, b, c); }          // run distToLine as above

double angle(point a, point o, point b) {  // returns angle aob in rad
    vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > 0; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }

vector<point> convex_hull(vector<point> Points) {

    //-------------- incremental alg. ---------
    // upper hull
    sort(Points.begin(), Points.end());
    stack<point> stk_up;
    stk_up.push(Points[0]);
    stk_up.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_up.size() >= 2)) {
            point p2, p3;
            p2 = stk_up.top();
            stk_up.pop();
            p3 = stk_up.top();
            if (ccw(Points[i], p2, p3)){
                stk_up.push(p2);
                break;
            }
        }
        stk_up.push(Points[i]);
    }
    // lower hull
    for (int i=0; i<Points.size(); i++) {
        Points[i].x = -Points[i].x;
        Points[i].y = -Points[i].y;
    }
    sort(Points.begin(), Points.end());
    stack<point> stk_low;
    stk_low.push(Points[0]);
    stk_low.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_low.size() >= 2)) {
            point p2, p3;
            p2 = stk_low.top();
            stk_low.pop();
            p3 = stk_low.top();
            if (ccw(Points[i], p2, p3)){
                stk_low.push(p2);
                break;
            }
        }
        stk_low.push(Points[i]);
    }

    // print convex hull - cw order from leftmost point
    vector<point> CH;
    stk_low.pop();
    point p;
    while (!stk_low.empty()) {
        p = stk_low.top();
        p.x = -p.x;
        p.y = -p.y;
        CH.push_back(p);
        stk_low.pop();
    }
    stk_up.pop();
    while (!stk_up.empty()) {
        CH.push_back(stk_up.top());
        stk_up.pop();
    }
    reverse(CH.begin(), CH.end());  // ccw -> cw
    return CH;
}

bool checkIn (vector<point>& C, point c)
{
    int h = C.size() -1, l = 1;
    point r;
    while (h > l +1)
    {
        int mid = (h+l)/2;
        if (collinear(C[0], C[mid], c))
            return distToLineSegment(c, C[0],C[mid],r) < 0.0000001;
        if (collinear(C[0], C[mid+1], c))
            return distToLineSegment(c, C[0],C[mid+1],r) < 0.0000001;
        if (mid>1 && collinear(C[0], C[mid+1], c))
            return distToLineSegment(c, C[0],C[mid-1],r) < 0.0000001;
        if (ccw(c,C[0],C[mid]))
            h=mid;
        else
            l=mid;
    }
    return (collinear(C[l],C[h],c) && ccw(C[0],C[l],c) == ccw(C[h],C[0], c)) ||
            (ccw(C[0],C[l],c) == ccw(C[l],C[h],c) && ccw(C[l],C[h],c) == ccw(C[h],C[0],c));
}


int main() {
    int L,S,res;
    double x,y;
    while (cin >> L)
    {
        res =0;
        vector<point> vp;
        for (int i = 0; i< L; i++)
        {
            cin >> x >>y;
            point p (x,y);
            vp.push_back(p);
        }
        vector<point> ch = convex_hull(vp);
        cin >> S;
        for (int i = 0; i< S; i++)
        {
            cin>>x >>y;
            point p (x,y);
            if (checkIn(ch,p))
                res++;
        }
        cout<< res<<endl;
    }
    return 0;
}
