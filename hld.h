#include <bits/stdc++.h>
#include "segtree.h"
using namespace std;

struct HLD {
    int n;
    vector<int> parent, depth, heavy, head, pos;
    Segtree<int> T;
    int cur_pos;
 
    int dfs(int v, vector<vector<int>> const& adj) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                int c_size = dfs(c, adj);
                size += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }
        }
        return size;
    }
 
    void decompose(int v, int h, vector<vector<int>> const& adj) {
        head[v] = h, pos[v] = cur_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h, adj);
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, adj);
        }
    }
 
    HLD(vector<vector<int>> const& adj, vector<int> const& val) : n(val.size()), T(n) {
        parent = vector<int>(n);
        depth = vector<int>(n);
        heavy = vector<int>(n, -1);
        head = vector<int>(n);
        pos = vector<int>(n);
        cur_pos = 0;
        dfs(0, adj);
        decompose(0, 0, adj);
        for(int i = 0; i < n; i++) T.update(pos[i], val[i]);
    }
 
    int query(int a, int b) {
        int res = 0;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            int cur_heavy_path_max = T.get(pos[head[b]], pos[b]);
            res = max(res, cur_heavy_path_max);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int last_heavy_path_max = T.get(pos[a], pos[b]);
        res = max(res, last_heavy_path_max);
        return res;
    }
 
    void update(int a, int b) {
        T.update(pos[a], b);
    }
};