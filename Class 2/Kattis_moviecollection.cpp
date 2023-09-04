#include <iostream>

using namespace std;

int BIT[200010], m, r;
void update(int x, int val) {
    for(; x <= m+r; x += x&-x)
        BIT[x] += val;
}

int query(int x)
{
    int sum = 0;
    for(; x > 0; x -= x&-x)
        sum += BIT[x];
    return sum;
}

int main ()
{
    int tests, a;
    cin >> tests;
    for (int i = 0; i < tests; i++)
    {
        cin >> m >> r;
        int top = m+1;
        int pos[m+1];
        for (int j = 0; j<200010; j++)
        {
            BIT[j] =0 ;
        }

        for (int j = 1; j<=m; j++)
        {
            pos[j] = m-j+1;
            update(j,1);
        }
        for (int j = 0; j<r; j++)
        {
            cin >> a;
            int output = m- query(pos[a]);
            cout << output << " ";
            update(pos[a], -1);
            pos[a] = top;
            update (top,1);
            top++;
        }
        cout << endl;
    }

    return 0;
}