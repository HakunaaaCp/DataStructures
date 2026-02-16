template<typename T> 
struct Lazy {
    int n;
    bool build_from_vector = false;
    vector<int> lo, hi;
    vector<T> t, a, ass, inc;
    void init() {
        lo.resize(4 * n);
        hi.resize(4 * n);
        t.resize(4 * n, T());
        ass.resize(4 * n, T());
        inc.resize(4 * n, T());
    }
    Lazy(int n) : n(n) {
        init();
        build(1, 0, n - 1);
    } 
    Lazy(const vector<T>& a) : n((int)a.size()), a(a) { 
        init();
        build_from_vector = 1;
        build(1, 0, n - 1);
    }
    void push(int u) {
        if(lo[u] == hi[u]) return;
        for(int i = 0; i < 2; i++) {
            int v = (u << 1) | i;
            int len = hi[v] - lo[v] + 1;

            if(ass[u] != T()) {        
                ass[v] = ass[u];
                t[v] = ass[u] * len;
                inc[v] = T();
            } 
            if(inc[u] != T()) { 
                inc[v] += inc[u];
                t[v] += inc[u] * len;
            }
        }
        ass[u] = T();
        inc[u] = T();
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
    T get(int u, int a, int b) {
        push(u);
        int l = lo[u], r = hi[u];
        if(l == a && r == b) return t[u];
        int m = (l + r) / 2;
        if(b <= m) return get(u << 1, a, b);
        else if(a > m) return get(u << 1 | 1, a, b);
        else return merge(get(u << 1, a, m), get(u << 1 | 1, m + 1, b));
    }
    T get(int a, int b) {
        return get(1, a, b);
    }
    void increase(int u, int a, int b, T val) {
        push(u);
        int l = lo[u], r = hi[u];
        if(l == a && r == b) {
            inc[u] += val;
            t[u] += val * (hi[u] - lo[u] + 1);
            return;
        }
        int m = (l + r) / 2;
        if(b <= m) increase(u << 1, a, b, val);
        else if(a > m) increase(u << 1 | 1, a, b, val);
        else {
            increase(u << 1, a, m, val);
            increase(u << 1 | 1, m + 1, b, val);
        }
        t[u] = merge(t[u << 1], t[u << 1 | 1]);
    }
    void increase(int a, int b, T val) {
        increase(1, a, b, val);
    }
    void assign(int u, int a, int b, T val) {
        push(u);
        int l = lo[u], r = hi[u];
        if(l == a && r == b) {
            ass[u] = val;
            inc[u] = 0; // no need. 
            t[u] = val * (hi[u] - lo[u] + 1);
            return;
        }
        int m = (l + r) / 2;
        if(b <= m) assign(u << 1, a, b, val);
        else if(a > m) assign(u << 1 | 1, a, b, val);
        else {
            assign(u << 1, a, m, val);
            assign(u << 1 | 1, m + 1, b, val);
        }
        t[u] = merge(t[u << 1], t[u << 1 | 1]);        
    }
    void assign(int a, int b, T val) {
        assign(1, a, b, val);
    }
};
