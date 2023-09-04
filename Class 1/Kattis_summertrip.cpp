
#include <iostream>
#include <string>

using namespace std;

int main()
{
    bool seen[125];
    int counter =0;
    string input;
    cin >> input;
    for (int i = 0; i<input.size(); i++)
    {
        for (int k = 96; k<123;k++)
        {
            seen[k] = false;
        }
        for (int j = i+1; j<input.size();j++)
        {
            if (input[i] == input[j])
                break;
            if (!seen[(int)input[j]])
            {
                counter++;
                seen[(int)input[j]] = true;
            }
        }

    }
    cout<<counter<<endl;
    return 0;
}