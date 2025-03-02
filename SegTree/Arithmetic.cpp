struct segtree {
    int n;
    vector<int> a;
    vector<long long> t;
    vector<array<int, 2>> pos;
    vector<array<long long, 2>> lz;

    segtree(int n) : n(n) {
        a.resize(n, 0); 
        t.resize(4 * n, 0);
        lz.resize(4 * n, {0, 0});
        pos.resize(4 * n);
        build(0, 0, n - 1);
    }

    segtree(const vector<int>& a) : segtree(a.size()) {
        this->a = a; 
        build(0, 0, n - 1);
    }

    void build(int u, int l, int r) {
        pos[u][0] = l;
        pos[u][1] = r;
        if(l == r) {
            t[u] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(u * 2 + 1, l, m);
        build(u * 2 + 2, m + 1, r);
        t[u] = t[u * 2 + 1] + t[u * 2 + 2];
    }

    int len(int u) {
        return pos[u][1] - pos[u][0] + 1;
    }

    int mid(int u) {
        return (pos[u][0] + pos[u][1]) / 2;
    }

    void push(int u) {
        if(lz[u][1]) {
            int l = pos[u][0], r = pos[u][1], m = mid(u);
            lz[u * 2 + 1][0] += lz[u][0];
            lz[u * 2 + 1][1] += lz[u][1];
            t[u * 2 + 1] += (2 * lz[u][0] + lz[u][1] * (m - l)) * (m - l + 1) / 2;

            lz[u * 2 + 2][0] += lz[u][0] + lz[u][1] * (m - l + 1);
            lz[u * 2 + 2][1] += lz[u][1];
            t[u * 2 + 2] += (2 * lz[u][0] + lz[u][1] * (m + r + 1 - 2 * l)) * (r - m) / 2;

            lz[u][0] = 0;
            lz[u][1] = 0;
        }
    }

    void update(int u, int l, int r, int a, int b, int val, int d) {
        if(l == a && r == b) {
            lz[u][0] += val;
            lz[u][1] += d;
            t[u] += (2 * val + (len(u) - 1) * d) * len(u) / 2;
            return;
        }
        push(u);
        int m = mid(u);
        if(b <= m) update(u * 2 + 1, l, m, a, b, val, d);
        else if(a > m) update(u * 2 + 2, m + 1, r, a, b, val, d);
        else {
            update(u * 2 + 1, l, m, a, m, val, d);
            update(u * 2 + 2, m + 1, r, m + 1, b, val + (m + 1 - a) * d, d);
        }
        t[u] = t[u * 2 + 1] + t[u * 2 + 2];
    }

    long long get(int u, int l, int r, int pos) {
        if(l == r) {
            assert(l == pos);
            return t[u];
        }
        push(u);
        int m = mid(u);
        if(pos <= m) return get(u * 2 + 1, l, m, pos);
        else return get(u * 2 + 2, m + 1, r, pos);
    }

    void update(int a, int b, int val, int d) {
        update(0, 0, n - 1, a, b, val, d);
    }

    long long get(int pos) {
        return get(0, 0, n - 1, pos);
    }
};