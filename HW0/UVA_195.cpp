#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>


using namespace std;

bool cmp (const char c1, const char c2)
{
    if ((c1 + 32 == c2) || (c1 -32 == c2))
        return c1 < c2;
    return std::tolower(c1) < std::tolower(c2);
}

int main()
{
    int n;
    string s;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin >> s;
        sort(s.begin(), s.end(),cmp);
        cout << s << endl;
        while(next_permutation(s.begin(), s.end(), cmp)){
            cout << s << endl;
        }
    }
    return 0;
}
