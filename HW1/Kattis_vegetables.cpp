#include <iostream>
#include <vector>

using namespace std;

int main() {
    double T;
    int N;
    cin >> T;
    cin >> N;
    double max = 0, min = 1000000;
    int i = 0, counter=0;
    vector<int> initial_weights(N);
    vector<double> cutted_weights(N);
    vector<int> cuts(N, 0);
    while (i < N) {
        int input;
        cin >> input;
        initial_weights[i] = input;
        cutted_weights[i] = input;
        if (input > max)
            max = input;
        if (input < min)
            min = input;
        i++;
    }

    while (min / max < T)
    {
        max =0;
        for (int j = 0;j<N;j++)
        {
            while (min/cutted_weights[j] < T)
            {
                cuts[j]++;
                cutted_weights[j] = initial_weights[j] / (cuts[j]+1);
            }
            if (cutted_weights[j] > max)
                max = cutted_weights[j];
            if (cutted_weights[j] < min)
                min = cutted_weights[j];
        }

    }
    for (int j =0; j<N;j++)
        counter = counter + cuts[j];
    cout<<counter<<endl;
    return 0;
}
