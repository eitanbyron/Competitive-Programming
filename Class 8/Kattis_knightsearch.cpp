#include <iostream>
#include <vector>

using namespace std;

#define FAVSIZE 10

int N;
string favorite = "ICPCASIASG";
vector<vector<char>> Chessland;
vector<int> axisx {1, 1, -1, -1, 2, 2, -2, -2};
vector<int> axisy {2, -2, 2, -2, 1, -1, 1, -1};

bool check(int x, int y, int char_index){
    if(char_index == FAVSIZE){
        return true;
    }
    if(x < 0 || x >= N || y < 0 || y >= N){
        return false;
    }
    if(Chessland[x][y] != favorite[char_index]){
        return false;
    }
    for(int i = 0; i < 8; i++){
        if(check(x + axisx[i], y + axisy[i], char_index + 1)){
            return true;
        }
    }
    return false;
}

int main() {
    cin>>N;
    bool found =false;
    Chessland.assign(N, vector<char>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> Chessland[i][j];
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(check(i, j, 0)){
                found =true;
            }
        }
    }
    if (found)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}