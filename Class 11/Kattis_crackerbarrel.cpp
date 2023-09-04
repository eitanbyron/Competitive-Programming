#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>


using namespace std;

vector<vector<pair<int, int>>> moves{{{1, 3}, {2, 5}},{{3, 6},{4, 8}}, {{4, 7}, {5, 9}},{{1, 0},{4, 5}, {6,10},{7,12}},
                                       {{7, 11}, {8, 13}},{{2, 0},{4, 3}, {8,12},{9,14}}, {{3, 1}, {7, 8}}, {{4, 2}, {8, 9}}
        ,{{4, 1}, {7, 6}}, {{5, 2}, {8, 7}},{{6, 3}, {11, 12}},{{7, 4}, {12, 13}},
                                       {{7, 3},{8, 5}, {11,10},{13,14}},{{8, 4}, {12,11}},{{9, 5}, {13,12}}};


unordered_map<string, int> colours;
unordered_map<long long , bool> memo;
int counter;

long long hashing(vector<int> &board)
{
    long long res = 0;
    for (int i = 0; i < 15; i++) {
        res = res * counter + board[i];
    }
    return res;
}


bool dp (long long board, int index)
{
    if (memo.find(board) != memo.end())
        return memo[board];
    int pegs =0;
    vector<int> vec(15);
    for (int i = 14; i >= 0; i--) {
        vec[i] = board % counter;
        if (vec[i] != 0)
            pegs++;
        board = board/counter;
    }
    if (pegs == 1) {
        for (int i = 0; i < 15; i++) {
            if (vec[i] != 0) {
                memo[board] = (vec[i] == index);
                return memo[board];
            }
        }
    }
    for (int i = 0; i < 15; i++) {
        if (vec[i] != 0) {
            for (auto &[remove, jumpto] : moves[i]) {
                if (vec[jumpto] == 0 && vec[remove] != 0) {
                    int captured = vec[remove];
                    vec[jumpto] = vec[i];
                    vec[i] = 0;
                    vec[remove] = 0;
                    long long new_board = hashing(vec);
                    if (dp(new_board, index)) {
                        memo[board] = true;
                        return memo[board];
                    }
                    vec[remove] = captured;
                    vec[i] = vec[jumpto];
                    vec[jumpto] = 0;
                }
            }
        }
    }
    memo[board] = false;
    return memo[board];
}

int main() {
    int target_index;
    string target;
    char peg[3];
    peg[2] = '\0';
    vector<int> board(15);
    cin >> target;
    while (target != "**")
    {
        counter =0;
        colours["__"] =0;
        counter++;
        target_index = counter;
        colours[target] = counter++;
        for (int i = 0; i < 15; i++) {
            cin >> peg[0];
            cin >> peg[1];
            if (colours.find(peg) == colours.end())
                colours[peg] = counter++;
            board[i] = colours[peg];
        }
        if (!(dp(hashing(board),target_index))) {
            cout << "Impossible" << endl;
        }
        else
            cout << "Possible" << endl;
        cin >> target;
        colours.clear();
    }
    return 0;
}