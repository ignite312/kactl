/**
 * Author: Soyeb Pervez Jim
* Description: Sparse Table O(1)query
* Time: O(nlogn) to build, O(1) query
 * Initial capacity must be a power of 2 (if provided).
 */
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
