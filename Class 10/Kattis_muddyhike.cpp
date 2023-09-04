//
// Created by barbe on 16/06/2023.
//
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int height, width;
vector<vector<int>> grid;
vector<vector<bool>> visited;

bool dfs(int row, int col, int mud_max_value) {
    if (col == width - 1) {
        return true;
    }

    visited[row][col] = true;

    vector<int> direction_col = {0, 0, 1, -1};
    vector<int> direction_row = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int new_col = col + direction_col[i];
        int new_row = row + direction_row[i];

        if (new_col >= 0 && new_col < width && new_row >= 0 && new_row < height && !visited[new_row][new_col] && grid[new_row][new_col] <= mud_max_value) {
            if (dfs(new_row, new_col, mud_max_value)) {
                return true;
            }
        }
    }

    return false;
}

bool canWalkWithMudMaxVal(int mud_max_value) {
    visited.assign(height, vector<bool>(width, false));

    for (int i = 0; i < height; i++) {
        if (grid[i][0] <= mud_max_value && dfs(i, 0, mud_max_value)) {
            return true;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> height >> width;

    grid.assign(height, vector<int>(width));

    int low = INT_MAX, high = 0;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            cin >> grid[row][col];
            high = max(high, grid[row][col]);
            low = min(low, grid[row][col]);
        }
    }

    int answer = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canWalkWithMudMaxVal(mid)) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << answer << endl;

    return 0;
}

