/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.setValue(2); // Var 2 is true
 *  ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
#pragma once

struct _2SAT {
    // 0-base indexing
    int n;
    vector<vector<int>> adj, radj;
    vector<int> todo, comps, id;
    vector<bool> vis, assignment;
    void init(int _n) {
        n = _n;
        adj.resize(n), radj.resize(n), id.assign(n, -1), vis.resize(n);
        assignment.assign(n/2, false);
    }
    void build(int x, int y) { adj[x].push_back(y), radj[y].push_back(x);}
    void dfs1(int x) {
        vis[x] = 1;
        for(auto y : adj[x]) if (!vis[y]) dfs1(y);
        todo.push_back(x);
    }
    void dfs2(int x, int v) {
        id[x] = v;
        for(auto y : radj[x]) if (id[y] == -1) dfs2(y, v);
    }
    bool solve_2SAT() {
        for(int i = 0; i < n; i++) if (!vis[i]) dfs1(i);
        reverse(todo.begin(), todo.end());
        int j = 0;
        for(auto x : todo) if (id[x] == -1) {
            dfs2(x, j++);
            // comps.push_back(x);
        }
        for (int i = 0; i < n; i += 2) {
            if (id[i] == id[i + 1]) {
                return false;
            }
            assignment[i / 2] = id[i] > id[i + 1];
        }
        return true;
    }
    void add_disjunction(int a, bool na, int b, bool nb) {
        // na and nb signify whether a and b are to be negated 
        a = 2 * a ^ na;
        b = 2 * b ^ nb;
        int neg_a = a ^ 1;
        int neg_b = b ^ 1;
        build(neg_a, b);
        build(neg_b, a);
    }
} _2sat;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n, m;
        cin >> n >> m;
        _2sat.init(m*2);
        for(int i = 0; i < n; i++) {
          int a, b;
          char _na, _nb;
          cin >> _na >> a >> _nb >> b;
          bool na, nb;
          --a, --b;
          if(_na == '+')na = false;
          else na = true;
          if(_nb == '+')nb = false;
          else nb = true;
          _2sat.add_disjunction(a, na, b, nb);
        }
        bool possible = _2sat.solve_2SAT();
        if(possible) {
          for(int i = 0; i < m; i++) {
            if(_2sat.assignment[i])cout <<"+ ";
            else cout << "- ";
          }
        }else cout << "IMPOSSIBLE";
    }
    return 0;
}