#include <iostream>
#include <string>
#include <cmath>


using namespace std;

int main() {
    string s;
    int size, num,temp =1, i=1;
    double sum = 0;
    cin >> s;
    size = s.size();
    if (size < 10)
    {
     num = stoi(s);
     while (true)
     {
       temp = temp *i;
         if (temp == num) {
             break;
         }
         i++;
     }
    }
    else
    {
        while (true) {
            sum += log10(i);
            if ((int)(sum+1) == size)
                break;
            i++;
        }

    }

    cout << i << endl;
    return 0;
}
