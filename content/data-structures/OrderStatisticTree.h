/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Time: O(\log N)
 */
#pragma once


#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 9;
struct HopcroftKarp {
  static const int inf = 1e9;
  int n;
  vector<int> l, r, d;
  vector<vector<int>> g;
  HopcroftKarp(int _n, int _m) {
    n = _n;
    int p = _n + _m + 1;
    g.resize(p);
    l.resize(p, 0);
    r.resize(p, 0);
    d.resize(p, 0);
  }
  void add_edge(int u, int v) {
    g[u].push_back(v + n);
  }
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
      if (!l[u]) d[u] = 0, q.push(u);
      else d[u] = inf;
    }
    d[0] = inf;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : g[u]) {
        if (d[r[v]] == inf) {
          d[r[v]] = d[u] + 1;
          q.push(r[v]);
        }
      }
    }
    return d[0] != inf;
  }
  bool dfs(int u) {
    if (!u) return true;
    for (auto v : g[u]) {
      if(d[r[v]] == d[u] + 1 && dfs(r[v])) {
        l[u] = v;
        r[v] = u;
        return true;
      }
    }
    d[u] = inf;
    return false;
  }
  int maximum_matching() {
    int ans = 0;
    while (bfs()) {
      for(int u = 1; u <= n; u++) if (!l[u] && dfs(u)) ans++;
    }
    return ans;
  }
};
int32_t main() {
  int n, m, q;
  cin >> n >> m >> q;
  HopcroftKarp M(n, m);
  while (q--) {
    int u, v; cin >> u >> v;
    M.add_edge(u, v);
  }
  cout << M.maximum_matching() << '\n';
  return 0;
}
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_pair_set tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set os;
// Example using ordered_set
os.insert(5);os.insert(1);os.insert(10);os.insert(3);
cout << "2nd smallest element: " << *os.find_by_order(2) << endl;  // Output: 5
cout << "Elements less than 6: " << os.order_of_key(6) << endl;  // Output: 3
// Example using ordered_pair_set
ordered_pair_set ops;
ops.insert({1, 100});ops.insert({2, 200});ops.insert({1, 150});ops.insert({3, 250});
cout << "1st smallest pair: (" << ops.find_by_order(0)->first << ", " << ops.find_by_order(0)->second << ")" << endl;  // Output: (1, 100)
cout << "Pairs less than (2, 150): " << ops.order_of_key({2, 150}) << endl;  // Output: 2
