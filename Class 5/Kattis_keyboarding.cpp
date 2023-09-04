#include <vector>
#include <iostream>
#include <queue>
#include <tuple>
const int iinf = 1e9 + 10;

using namespace std;
int rows, cols;

bool inrange(int x, int y) {
    return (x >= 0) && (y >= 0) && (x < rows) && (y < cols);
}

int main() {

    cin >> rows >> cols;

    vector<vector<char>> board;
    board.resize(rows, vector<char>(cols));

    for(auto& i : board) {
        for(auto& j : i) {
            cin >> j;
        }
    }

    string s;
    cin >> s;
    s += "*";

    vector<vector<vector<int>>> vis;
    vis.resize(rows, vector<vector<int>>(cols, vector<int>(s.size() + 1, iinf)));

    queue<tuple<int,int,int>> q;
    vis[0][0][0] = 0;
    q.push({0,0,0});

    int dist = iinf;
    while(!q.empty()) {
        int x, y, len;
        tie(x, y, len) = q.front();
        q.pop();

        if(len == s.length()) {
            dist = vis[x][y][len];
            break;
        }

        if(board[x][y] == s[len]) {
            if(vis[x][y][len + 1] > vis[x][y][len] + 1) {
                vis[x][y][len + 1] = vis[x][y][len] + 1;
                q.push({x, y, len + 1});
            }
        }

        int nextx, nexty;

        nextx = x;
        while(true) {
            nextx--;
            if(nextx < 0) {
                break;
            }

            if(board[x][y] != board[nextx][y]) {
                if(vis[nextx][y][len] > vis[x][y][len] + 1) {
                    vis[nextx][y][len] = vis[x][y][len] + 1;
                    q.push({nextx, y, len});
                }
                break;
            }
        }

        nextx = x;
        while(true) {
            nextx++;
            if(nextx >= rows) {
                break;
            }

            if(board[x][y] != board[nextx][y]) {
                if(vis[nextx][y][len] > vis[x][y][len] + 1) {
                    vis[nextx][y][len] = vis[x][y][len] + 1;
                    q.push({nextx, y, len});
                }
                break;
            }
        }

        nexty = y;
        while(true) {
            nexty--;
            if(nexty < 0) {
                break;
            }

            if(board[x][y] != board[x][nexty]) {
                if(vis[x][nexty][len] > vis[x][y][len] + 1) {
                    vis[x][nexty][len] = vis[x][y][len] + 1;
                    q.push({x, nexty, len});
                }
                break;
            }
        }

        nexty = y;
        while(true) {
            nexty++;
            if(nexty >= cols) {
                break;
            }

            if(board[x][y] != board[x][nexty]) {
                if(vis[x][nexty][len] > vis[x][y][len] + 1) {
                    vis[x][nexty][len] = vis[x][y][len] + 1;
                    q.push({x, nexty, len});
                }
                break;
            }
        }
    }

    cout << dist << endl;

    return 0;
}