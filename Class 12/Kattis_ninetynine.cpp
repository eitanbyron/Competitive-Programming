//
// Created by barbe on 27/06/2023.
//
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <chrono>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
#define EPS 1e-9
#define MAX_SIZE 100
using namespace std;
#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

int main() {
    int num = 1;
    while(num!= 99){
        cout << num << endl;
        cin >> num;
        if(num == 93){
            num+=2;
        }
        else if(num % 3 == 1 ){
            num += 2;

        }
        else if(num % 3 == 2|| num % 3 == 0){
            num += 1;
        }
    }
    cout << num << endl;

    return 0;
}

