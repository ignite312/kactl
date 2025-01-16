/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
#pragma once

void make_set(int v) {
    parent[v] = v;
    Size[v] = 1;
}
int find_set(int v) {
    if (v == parent[v])return v;
    return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if(Size[a] < Size[b])swap(a, b);
        parent[b] = a;
        Size[a]+=Size[b];
    }
}
