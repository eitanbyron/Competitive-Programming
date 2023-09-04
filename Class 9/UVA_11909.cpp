#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

#define PI acos(-1.0)

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }


int main() {
    int l, w, h, theta;
    double res,d;
    while(cin >> l >> w >> h >> theta) {
        d=l*tan(DEG_to_RAD(theta));
        if(d > h)
            res=0.5*h*h*l*w/d;
        else
            res=l*w*((h)-(d*0.5));
        cout << fixed << setprecision(3) << res << " mL" << endl;
    }
    return 0;
}