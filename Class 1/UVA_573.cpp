#include <iostream>

using namespace std;

int main()
{
    double h, u, d, f;
    while (cin>>h>>u>>d>>f&&h!=0){
        if (h==0 && u ==0 && d==0 && f==0)
            break;
        double fatigue = f*u/100;
        double progress =0;
        int day = 1;
        while (1)
        {
            progress = progress + u;
            if (progress > h){
                cout << "success on day " << day << endl;
                break;
            }
            if(u-fatigue < 0)
                u=0;
            else
                u=u-fatigue;
            progress = progress -d;
            if (progress < 0){
                cout << "failure on day " << day << endl;
                break;
            }
            day++;
        }
    }
    return 0;
}