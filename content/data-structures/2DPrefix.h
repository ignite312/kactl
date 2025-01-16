/**
 * Author: Emon
 * Date: 
 * License: 
 * Source: 
 * Description: 2D prefix with update
 * Usage:
 * SubMatrix<int> m(matrix);
 * m.sum(0, 0, 2, 2); // top left 4 elements
 * Time: O(N^2 + Q)
 * Status: Tested on Kattis
 */
#pragma once

void update(vector<vector<ll>>& grid, int x1, int y1, int x2, int y2, int val) {
    grid[x1][y1] += val;
    if (x2 + 1 < n) grid[x2 + 1][y1] -= val;
    if (y2 + 1 < m) grid[x1][y2 + 1] -= val;
    if (x2 + 1 < n && y2 + 1 < m) grid[x2 + 1][y2 + 1] += val;
}
vector<vector<ll>> calculate(vector<vector<ll>> &grid) {
    vector<vector<ll>> ans(n, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans[i][j] = grid[i][j];
            if(i > 0) ans[i][j] += ans[i - 1][j];
            if(j > 0) ans[i][j] += ans[i][j - 1];
            if(i > 0 && j > 0) ans[i][j] -= ans[i - 1][j - 1];
        }
    }
    return ans;
}