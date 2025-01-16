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
template<class T> struct SubMatrix {
    vector<vector<T>> p;
    SubMatrix(const vector<vector<T>>& v) {
        int R = v.size(), C = v[0].size();
        p.assign(R + 1, vector<T>(C + 1, 0));
        
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                p[r + 1][c + 1] = v[r][c] + p[r][c + 1] + p[r + 1][c] - p[r][c];
            }
        }
    }
    T sum(int u, int l, int d, int r) {
        return p[d + 1][r + 1] - p[u][r + 1] - p[d + 1][l] + p[u][l];
    }
};