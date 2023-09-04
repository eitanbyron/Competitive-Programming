#include <iostream>

using namespace std;

string area (int num)
{
    switch (num) {
        case 1:
            return "single";
        case 2:
            return "double";
        case 3:
            return "triple";
    }
}

int main() {
    int n,t1,t2,t3;
    cin >> n;
    for (int i = 1; i<=20; i++)
    {
        for (int a =1; a<=3; a++)
        {
            t1 = n;
            t1 -= a*i;
            for (int j = 0; j<=20; j++)
            {
                for (int b =1; b<=3; b++)
                {
                    t2 =t1;
                    t2 -= j*b;
                    for (int k = 0; k<=20; k++)
                    {
                        for (int c =1; c<=3; c++)
                        {
                            t3 =t2;
                            t3 -= k*c;
                            if (t3 == 0)
                            {
                                cout << area(a) << " " << i <<endl;
                                if (j != 0)
                                    cout << area(b) << " " << j <<endl;
                                if (k!=0)
                                    cout << area(c) << " " << k <<endl;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "impossible" << endl;
    return 0;
}