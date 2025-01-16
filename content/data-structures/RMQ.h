/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

struct ST {
    // 0-base indexing
  int n, logN;
  vector<vector<int>> st;
  vector<int> lg;
 
  void init(const vector<int>& array) {
    n = array.size();
    logN = ceil(log2(n));
    st.resize(logN, vector<int>(n));
    lg.resize(n + 1);
 
    lg[1] = 0;
    for (int i = 2; i <= n; i++)
      lg[i] = lg[i / 2] + 1;
 
    copy(array.begin(), array.end(), st[0].begin());
 
    for (int i = 1; i < logN; i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int query(int L, int R) {
    int i = lg[R - L + 1];
    return min(st[i][L], st[i][R - (1 << i) + 1]);
  }
} ST;
