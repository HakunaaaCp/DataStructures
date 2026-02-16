template<typename T> 
struct Segtree {
    int n;
    bool build_from_vector = false;
    vector<int> lo, hi;
    vector<T> t, a; 
    void init() {
        lo.resize(4 * n);
        hi.resize(4 * n);
        t.resize(4 * n);
    }
    Segtree(int n) : n(n) {
        init();
        build(1, 0, n - 1);
    } 
    Segtree(const vector<T>& a) : n((int)a.size()), a(a) { 
        init();
        build_from_vector = 1;
        build(1, 0, n - 1);
    }
    static T merge(const T& a, const T& b) {
        return a + b;
    }
    void build(int u, int l, int r) {
        lo[u] = l, hi[u] = r;
        if(l == r) {
            if(build_from_vector) t[u] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(u << 1, l, m);
        build(u << 1 | 1, m + 1, r);
        if(build_from_vector) t[u] = merge(t[u << 1], t[u << 1 | 1]);
    }
    T get(int u, int a, int b) const {
        int l = lo[u], r = hi[u];
        if(l == a && r == b) return t[u];
        int m = (l + r) / 2;
        if(b <= m) return get(u << 1, a, b);
        else if(a > m) return get(u << 1 | 1, a, b);
        else return merge(get(u << 1, a, m), get(u << 1 | 1, m + 1, b));
    }
    T get(int a, int b) const {
        return get(1, a, b);
    }
    void update(int u, int pos, T val) {
        int l = lo[u], r = hi[u];
        if(l == r) {
            assert(l == pos);
            t[u] = val;
            return;
        }
        int m = (l + r) / 2;
        if(pos <= m) update(u << 1, pos, val);
        else update(u << 1 | 1, pos, val);
        t[u] = merge(t[u << 1], t[u << 1 | 1]);
    }
    void update(int pos, T val) {
        update(1, pos, val);
    }
};
