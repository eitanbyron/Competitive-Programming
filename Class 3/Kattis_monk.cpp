#include <iostream>
#include <vector>
#include <iomanip>



using namespace std;
long double s =0,h_asc[5001], t_asc[5001], h_des[5001], t_des[5001];
int a,d;


bool check (long double num)
{
    long double x =0,y=0, n =num;
    for (int i =0; i<a;i++)
    {
        if (n<=0)
            break;
        x= x+min(h_asc[i], n/(t_asc[i])*h_asc[i]);
        n = n-min(n,t_asc[i]);
    }
    n=num;
    for (int i =0; i<d;i++)
    {
        if (n<=0)
            break;
        y= y+min(h_des[i], n/(t_des[i])*h_des[i]);
        n = n-min(n,t_des[i]);
    }
    y =s-y;
    return (x>=y);
}

int main() {
    cin >> a >> d;
    long double mid, l = 0.0, r = 0.0;
    for (int i = 0; i < a; i++) {
        cin >> h_asc[i] >> t_asc[i];
        r = r + t_asc[i];
        s = s + h_asc[i];
    }
    for (int i = 0; i < d; i++) {
        cin >> h_des[i] >> t_des[i];
    }
    while (abs(l - r) > 1e-8) {
        mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    cout << fixed << setprecision(6) << r << endl;
    return 0;
}