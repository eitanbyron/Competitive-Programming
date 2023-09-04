#include <iostream>
#include <vector>
#include<algorithm>



using namespace std;

int main()
{
    int n;
    long long k;
    cin >> n;
    cin >> k;
    vector<long long> a(n);
    vector<long long> b(n);
    for (int i=0; i<n;i++)
    {
        cin >> a[i];
        cin >> b[i];
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int pa=0,pb=0, max = -1;
    int temp = 0;
    while (pa < n)
    {
        if (a[pa]- b[pb] <= k)
        {
            temp++;
            pa++;
            if (temp > max)
                max =temp;
        }
        else
        {
            while (a[pa]- b[pb] > k)
            {
                pb++;
                temp--;
            }
        }
    }
    cout << max<<endl;
    return 0;
}