#include <iostream>
#include <vector>
#include <queue>


using namespace std;

int main()
{
    int K,M,N;
    int iterator=0;
    cin >> M >>N;
    priority_queue<int, vector<int>, greater<int> > min_heap;
    priority_queue<int> max_heap;
    vector<int> add(M);
    for (int j=0;j<M;j++)
    {
        cin >> add[j];
    }
    for (int j=0;j<N;j++) {
        int temp;
        cin >> temp;
        while (iterator<temp)
        {
            if (max_heap.empty())
                min_heap.push(add[iterator]);
            else
            {
                if (add[iterator] < max_heap.top())
                {
                    max_heap.push(add[iterator]);
                    min_heap.push(max_heap.top());
                    max_heap.pop();
                }
                else
                {
                    min_heap.push(add[iterator]);
                }
            }
            iterator++;
        }
        cout <<min_heap.top()<<endl;
        max_heap.push(min_heap.top());
        min_heap.pop();
    }
    return 0;
}