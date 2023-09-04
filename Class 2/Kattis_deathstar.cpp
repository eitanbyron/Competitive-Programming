#include <iostream>
#include <vector>

using namespace std;



int main ()
{
    int N, organ, output;
    cin >> N;
    vector<vector<int>> matrix;
    for (int i = 0; i<N; i++)
    {
        vector<int> temp;
        for (int j= 0; j<N; j++)
        {
            cin >> organ;
            temp.push_back(organ);
        }
        matrix.push_back(temp);
    }

    for (int i = 0; i<N; i++) {
        output =0;
        for (int j= 0; j<N; j++)
        {
          if (i == j)
              continue;
          output = output | matrix[i][j];
        }
        cout << output << " ";
    }

    return 0;
}