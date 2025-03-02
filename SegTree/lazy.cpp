struct segtree {
    int n;
    vector<int> a, len;
    vector<long long> t, ass, inc;

    segtree(int n) : n(n) {
        t.resize(4 * n);
        inc.resize(4 * n, 0);
        ass.resize(4 * n, 0);
        len.resize(4 * n);
    }

    segtree(const vector<int>& a) : segtree(a.size()) {
        this->a = a;
        build(0, 0, n - 1);
    }

    void build(int u, int l, int r) {
        len[u] = r - l + 1;
        if (l == r) {
            t[u] = a[l];
        } else {
            int m = (l + r) / 2;
            build(u * 2 + 1, l, m);
            build(u * 2 + 2, m + 1, r);
            t[u] = t[u * 2 + 1] + t[u * 2 + 2];
        }
    }

    void push(int u) {
        if (ass[u]) {
            for (int i = 1; i <= 2; i++) {
                ass[u * 2 + i] = ass[u];
                t[u * 2 + i] = len[u * 2 + i] * ass[u];
                inc[u * 2 + i] = 0;
            }
            ass[u] = 0;
        }
        if (inc[u]) {
            for (int i = 1; i <= 2; i++) {
                inc[u * 2 + i] += inc[u];
                t[u * 2 + i] += len[u * 2 + i] * inc[u];
            }
            inc[u] = 0;
        }
    }

    void increase(int u, int l, int r, int a, int b, int val) {
        if (l == a && r == b) {
            inc[u] += val;
            t[u] += len[u] * val;
        } else {
            push(u);
            int m = (l + r) / 2;
            if (b <= m) increase(u * 2 + 1, l, m, a, b, val);
            else if (a > m) increase(u * 2 + 2, m + 1, r, a, b, val);
            else {
                increase(u * 2 + 1, l, m, a, m, val);
                increase(u * 2 + 2, m + 1, r, m + 1, b, val);
            }
            t[u] = t[u * 2 + 1] + t[u * 2 + 2];
        }
    }

    void increase(int a, int b, int val) {
        increase(0, 0, n - 1, a, b, val);
    }

    void assign(int u, int l, int r, int a, int b, int val) {
        if (l == a && r == b) {
            ass[u] = val;
            inc[u] = 0;
            t[u] = len[u] * val;
        } else {
            push(u);
            int m = (l + r) / 2;
            if (b <= m) assign(u * 2 + 1, l, m, a, b, val);
            else if (a > m) assign(u * 2 + 2, m + 1, r, a, b, val);
            else {
                assign(u * 2 + 1, l, m, a, m, val);
                assign(u * 2 + 2, m + 1, r, m + 1, b, val);
            }
            t[u] = t[u * 2 + 1] + t[u * 2 + 2];
        }
    }

    void assign(int a, int b, int val) {
        assign(0, 0, n - 1, a, b, val);
    }

    long long get(int u, int l, int r, int a, int b) {
        if (l == a && r == b) return t[u];
        else {
            push(u);
            int m = (l + r) / 2;
            if (b <= m) return get(u * 2 + 1, l, m, a, b);
            else if (a > m) return get(u * 2 + 2, m + 1, r, a, b);
            else return get(u * 2 + 1, l, m, a, m) + get(u * 2 + 2, m + 1, r, m + 1, b);
        }
    }

    long long get(int a, int b) {
        return get(0, 0, n - 1, a, b);
    }
};