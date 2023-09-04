#include <iostream>

using namespace std;

int main()
{
    int width, w, l, n;
    int space =0;
    cin>>width;
    cin>>n;
    for (int i =0; i <n;i++)
    {
        cin>>w;
        cin>>l;
        space = space+(w*l);
    }
    cout<<(space/width)<<endl;
    return 0;
}