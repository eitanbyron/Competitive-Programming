
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double statues;
    cin >> statues;
    int result = 1+ ceil(log(statues) / log(2));
    cout<< result << endl;
    return 0;
}