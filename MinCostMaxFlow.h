#include<bits/stdc++.h>
using namespace std;

const int N = 502, INF = INT_MAX;

struct Edge {
    int from, to, cap, flow, cost;
};

struct Flow {
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[N];
    int p[N],inq[N];
    int d[N];
    int a[N];
    Flow (int n) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void add_edge(int from,int to,int cap,int cost) {
        edges.push_back((Edge){from, to, cap, 0, cost});
        edges.push_back((Edge){to, from, 0, 0, -cost});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    pair<int,int> min_cost(int s,int t) {
        int tot_cost = 0;
        int tot_flow = 0;
        while(true) {
            for(int i = 0; i < n; i++) d[i] = INF;
            memset(inq, 0, sizeof(inq));
            d[s] = 0;
            inq[s] = 1;
            p[s] = 0;
            a[s] = INF;
            queue<int> Q;
            srand(time(NULL));
            Q.push(s);
            while(!Q.empty()) {
                int u = Q.front();
                Q.pop();
                inq[u] = 0;
                for(int i = 0; i < G[u].size(); i++) {
                    Edge& e = edges[G[u][i]];
                    if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                        d[e.to] = d[u] + e.cost;
                        p[e.to] = G[u][i];
                        a[e.to] = min(a[u], e.cap - e.flow);
                        if(!inq[e.to]) {
                            Q.push(e.to);
                            inq[e.to] = 1;
                        }
                    }
                }
            }
            if(d[t] == INF) break;
            tot_cost += (int)d[t] * a[t];
            tot_flow += a[t];
            int u = t;
            while(u != s) {
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
                u = edges[p[u]].from;
            }
        }

        return {tot_cost,tot_flow};
    }
};