#include "header.h"

struct Dsu {
    int n;
    vector<int> p, sz;
    Dsu(int n) : n(n) {
        p.resize(n);
        for(int i = 0; i < n; i++) p[i] = i;
        sz.resize(n, 1);
    }
    int find(int u) {
        if(u == p[u]) return u;
        else return p[u] = find(p[u]);
    }
    void unitn(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return;
        if(sz[b] > sz[a]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
    bool checK(int a, int b) {
        a = find(a), b = find(b);
        return a == b;
    }
};