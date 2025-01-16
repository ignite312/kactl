/**
 * Author: Farhan
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: PresistentSegment Tree
 */

struct persistentSegtree {
    // 0 base indexing
    ll data;
    persistentSegtree *left, *right;

    ll merge(ll x, ll y) {
        return x + y;
    }
    void build(vector<ll> &a, int l, int r) {
        if(l == r) {
            data = a[l];
            return;
        }
        int mid = l + ((r - l) >> 1);
        left = new persistentSegtree();
        right = new persistentSegtree();
        left->build(a, l, mid);
        right->build(a, mid+1, r);
        data = merge(left->data, right->data);
    }
    persistentSegtree* update(int i, ll value, int l, int r) {
        if(l > i || r < i) return this;
        if(l == i && r == i) {
            persistentSegtree *rslt = new persistentSegtree();
            rslt->data = value;
            return rslt;
        }
        int mid = l + ((r-l) >> 1);
        persistentSegtree *rslt = new persistentSegtree();

        rslt->left = left->update(i, value, l, mid);
        rslt->right = right->update(i, value, mid+1, r);
        rslt->data = merge(rslt->left->data, rslt->right->data);

        return rslt;
    }
    ll query(int i, int j, int l, int r) {
        if(l > j || r < i) return 0;
        if(l >= i && r <= j)return data;
        int mid = l + ((r - l) >> 1);
        return merge(left->query(i, j, l, mid), right->query(i, j, mid+1, r));
    }
} *roots[N];

roots[0] = new persistentSegtree();
roots[k++]->build(a, 0, n-1);
roots[_k] = roots[_k]->update(--i, x, 0, n-1);
cout << roots[--_k]->query(--i, --j, 0, n-1) << "\n";
roots[k++] = roots[--_k];