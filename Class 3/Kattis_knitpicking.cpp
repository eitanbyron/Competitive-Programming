#include <iostream>
#include <map>
#include <vector>



using namespace std;

int main() {
    int n, k, sum =0;
    bool f =false;
    cin >> n;
    string type, fit;
    map<pair<string,string>, int> mp;
    map <string,bool> flag;
    vector<pair<pair<string,string>, int>> vec;
    vector<string> temp;
    for (int i=0; i< n;i++)
    {
        cin >> type >> fit >>k;
        pair<string,string> p;
        p.first = type;
        p.second = fit;
        vec.push_back(make_pair(p,k));
        mp[p] = k;
        if (!flag[type])
        {
            flag[type] = true;
            temp.push_back(type);
        }
    }
        for (int j=0; j<temp.size(); j++)
        {
            int left =0, right =0, any =0;
            left = mp[make_pair(temp[j],"left")];
            right = mp[make_pair(temp[j],"right")];
            any = mp[make_pair(temp[j],"any")];
            sum =sum +max(left,right);
            if (left == 0 && right ==0)
                sum++;
            if ((right >0 && left >0) || (right >0 && any >0) || (left >0 && any >0) || (any >1))
                f= true;
        }
            if (f)
                cout<<sum+1<< endl;
            else
                cout<<"impossible"<<endl;

    return 0;
}
