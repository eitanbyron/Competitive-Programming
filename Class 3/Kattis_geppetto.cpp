#include <iostream>
#include <vector>


using namespace std;

long long res =0;
int counter[21];
vector <long long> cond[21];

void brute(int i, int n)
{
    counter[i]++;
    res++;
    for (int k:cond[i])
    {
        counter[k]++;
    }
    for (int k=i+1; k<= n ; k++)
    {
        if (!counter[k])
            brute(k,n);
    }
    counter[i]--;
    for (int k: cond[i])
    {
        counter[k]--;
    }
}



int main() {
    int n, m, temp1, temp2;
    cin >> n >> m;
    for (int i= 0; i< m; i++)
    {
        cin >> temp1 >>temp2;
        cond[temp1].push_back(temp2);
        cond[temp2].push_back(temp1);
    }

    for (int j= 1; j<= n; j++)
    {
       brute(j, n);
    }
    cout <<res+1<<endl;
    return 0;
}
