template<typename T>
struct segtree {
    int n;
    vector<T> a;
    vector<array<T, 3>> t;

    segtree(int n) : n(n), a(n, 0), t(4 * n) {}

    segtree(const vector<T>& a) : segtree(a.size()) {
        this->a = a;
        build(0, 0, n - 1);
    }

    array<T, 3> combine(const array<T, 3>& x, const array<T, 3>& y) {
        return {min(x[0], y[0]), max(x[1], y[1]), x[2] + y[2]};
    }

    void build(int u, int l, int r) {
        if (l == r) {
            t[u] = {a[l], a[l], a[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(u * 2 + 1, l, mid);
        build(u * 2 + 2, mid + 1, r);
        t[u] = combine(t[u * 2 + 1], t[u * 2 + 2]);
    }

    array<T, 3> get(int u, int l, int r, int a, int b) {
        if (l == a && r == b) return t[u];
        int mid = (l + r) / 2;
        if (b <= mid) return get(u * 2 + 1, l, mid, a, b);
        if (a > mid) return get(u * 2 + 2, mid + 1, r, a, b);
        return combine(get(u * 2 + 1, l, mid, a, mid), get(u * 2 + 2, mid + 1, r, mid + 1, b));
    }

    void update(int u, int l, int r, int pos, T val) {
        if (l == r) {
            t[u] = {val, val, val};
            return;
        }
        int mid = (l + r) / 2;
        if (pos > mid) update(u * 2 + 2, mid + 1, r, pos, val);
        else update(u * 2 + 1, l, mid, pos, val);
        t[u] = combine(t[u * 2 + 1], t[u * 2 + 2]);
    }

    int index(int u, int l, int r, T val) {
        if(t[u][1] < val) return -1;
        if(l == r) {
            assert(t[u][1] >= val);
            return l;
        }
        int m = (l + r) / 2;
        if(t[u * 2 + 1][1] >= val) return index(u * 2 + 1, l, m, val);
        else return index(u * 2 + 2, m + 1, r, val);
    }

    array<T, 3> get(int a, int b) {
        return get(0, 0, n - 1, a, b);
    }

    void update(int pos, T val) {
        update(0, 0, n - 1, pos, val);
    }

    int index(int val) {
        return index(0, 0, n - 1, val);
    }
};