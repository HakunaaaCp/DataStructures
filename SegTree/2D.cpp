struct Segtree2D {
    int n, m;
    vector<vector<int>> a;
    vector<vector<long long>> t;

    Segtree2D(int n, int m) : n(n), m(m) {
        t.resize(4 * n, vector<long long>(4 * m));
        a.resize(n, vector<int>(m, 0));
    }

    Segtree2D(const vector<vector<int>>& a) : n(a.size()), m(a[0].size()), a(a) {
        t.resize(4 * n, vector<long long>(4 * m));
        build_x(0, 0, n - 1);
    }

    void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {
        if(ly == ry) {
            if(lx == rx)
                t[vx][vy] = a[lx][ly];
            else
                t[vx][vy] = t[vx * 2 + 1][vy] + t[vx * 2 + 2][vy];
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, rx, vy * 2 + 1, ly, my);
            build_y(vx, lx, rx, vy * 2 + 2, my + 1, ry);
            t[vx][vy] = t[vx][vy * 2 + 1] + t[vx][vy * 2 + 2];
        }
    }

    void build_x(int vx, int lx, int rx) {
        if(lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(vx * 2 + 1, lx, mx);
            build_x(vx * 2 + 2, mx + 1, rx);
        }
        build_y(vx, lx, rx, 0, 0, m - 1);
    }

    long long sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
        if(ly > ry) return 0;
        if(ly == tly && try_ == ry) return t[vx][vy];
        int tmy = (tly + try_) / 2;
        return sum_y(vx, vy * 2 + 1, tly, tmy, ly, min(ry, tmy)) +
               sum_y(vx, vy * 2 + 2, tmy + 1, try_, max(ly, tmy + 1), ry);
    }

    long long sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
        if(lx > rx) return 0;
        if(lx == tlx && trx == rx) return sum_y(vx, 0, 0, m - 1, ly, ry);
        int tmx = (tlx + trx) / 2;
        return sum_x(vx * 2 + 1, tlx, tmx, lx, min(rx, tmx), ly, ry) +
               sum_x(vx * 2 + 2, tmx + 1, trx, max(lx, tmx + 1), rx, ly, ry);
    }

    void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
        if(ly == ry) {
            if(lx == rx)
                t[vx][vy] = new_val;
            else
                t[vx][vy] = t[vx * 2 + 1][vy] + t[vx * 2 + 2][vy];
        } else {
            int my = (ly + ry) / 2;
            if(y <= my)
                update_y(vx, lx, rx, vy * 2 + 1, ly, my, x, y, new_val);
            else
                update_y(vx, lx, rx, vy * 2 + 2, my + 1, ry, x, y, new_val);
            t[vx][vy] = t[vx][vy * 2 + 1] + t[vx][vy * 2 + 2];
        }
    }

    void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
        if(lx != rx) {
            int mx = (lx + rx) / 2;
            if(x <= mx)
                update_x(vx * 2 + 1, lx, mx, x, y, new_val);
            else
                update_x(vx * 2 + 2, mx + 1, rx, x, y, new_val);
        }
        update_y(vx, lx, rx, 0, 0, m - 1, x, y, new_val);
    }

    long long query(int lx, int rx, int ly, int ry) {
        return sum_x(0, 0, n - 1, lx, rx, ly, ry);
    }

    void update(int x, int y, int new_val) {
        update_x(0, 0, n - 1, x, y, new_val);
    }
};