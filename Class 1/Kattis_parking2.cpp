#include <iostream>

using namespace std;

int main()
{
    int tests, stores, temp;
    cin >> tests;
    for (int i =0; i <tests; i++)
    {
        cin >> stores;
        int right = -1;
        int left =100;
        for (int j = 0; j< stores; j++)
        {
            cin >> temp;
            if (temp < left)
                left = temp;
            if (temp > right)
                right = temp;
        }
        cout << 2*(right-left) <<endl;
    }
    return 0;
}
