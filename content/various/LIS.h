/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices for the longest increasing subsequence.
 * Time: $O(N \log N)$
 * Status: Tested on kattis:longincsubseq, stress-tested
 */
#pragma once

// Complexity: O(nlog(n))
int lis(int n, vector<int> &a) {
    vector<int> d(n+1, INF);
    d[0] = -INF;
    for(int i = 0; i < n; i++) {
        int idx = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
        d[idx] = a[i];
    }
    int ans = 1;
    for(int i = 1; i <= n; i++)if(d[i] < INF)ans = i;
    return ans;
}

// Cp-Algo Complexity: O(n^2)
vector<int> lis(vector<int> const& a) {
    int n = a.size();
    vector<int> d(n, 1), p(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && d[i] < d[j] + 1) {
                d[i] = d[j] + 1;
                p[i] = j;
            }
        }
    }
    int ans = d[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (d[i] > ans) {
            ans = d[i];
            pos = i;
        }
    }
    vector<int> sq;
    while (pos != -1) {
        sq.push_back(a[pos]);
        pos = p[pos];
    }
    reverse(sq.begin(), sq.end());
    return sq;
}
