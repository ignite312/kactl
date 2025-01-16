/**
 * Author: Emon
 * Description: Heavy Light Decomposition
 */
/*
Problem Name: Round Trip II(Directed)
Problem Link: https://cses.fi/problemset/task/1678/
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 100000;
vector<int> adj[N+1], parent(N+1);
vector<int> color(N+1);
int st, en;
 
bool dfs(int u) {
    color[u] = 1;
    for(auto v : adj[u]) {
        if(!color[v]) {
            parent[v] = u;
            if(dfs(v)) return true;
        }else if(color[v] == 1) {
            st = v, en = u;
            return true;
        }
    }
    color[u] = 2;
    return false;
}
void checkCycle(int n) {
    st = en = -1;
    for(int i = 1; i <= n; i++) {
        if(!color[i] && dfs(i)) {
            break;
        }
    }
    if(st == -1) cout << "IMPOSSIBLE\n";
    else {
        vector<int> path;
        path.push_back(st);
        for(int i = en; i != st; i = parent[i])path.push_back(i);
        path.push_back(st);
        reverse(path.begin(), path.end());
        cout << path.size() << "\n";
        for(auto i : path)cout << i << " ";
        cout << "\n";
    }
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  while(tt--) {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    checkCycle(n);
  }
  return 0;
}
/*
Problem Name: Round Trip(Undirected)
Problem Link: https://cses.fi/problemset/task/1669/
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
vector<int> adj[N + 1];
bool vis[N + 1], cycle_found;
int parent[N + 1], en, st;

void dfs(int u, int p) {
    vis[u] = true;
    for (auto v : adj[u]) {
        if (p == v)
            continue;
        if (!vis[v]) {
            parent[v] = u;
            dfs(v, u);
        }
        else {
            if (!cycle_found)
                en = u, st = v;
            cycle_found = true;
            return;
        }
    }
}

void checkCycle(int n) {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            parent[i] = -1;
            dfs(i, -1);
        }
    }
    if (!cycle_found) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    vector<int> path;
    path.push_back(st);
    path.push_back(en);
    int j = en;
    while (parent[j] != st) {
        path.push_back(parent[j]);
        j = parent[j];
    }
    path.push_back(st);
    cout << path.size() << "\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while (tt--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        checkCycle(n);
    }
    return 0;
}