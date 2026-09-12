struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

struct Dinic{
    int n, s, t;
    vector<vector<Edge>> Ed;
    vector<vector<int>> g;
    vector<int> d, ptr;

    Dinic() = default;
    Dinic(int _n, int _s, int _t){
        n = _n;
        s = _s;
        t = _t;
        Ed.resize(n + 5);
        for(int i=1; i<=n; ++i) Ed[i].resize(n + 5);
        g.resize(n + 5);
        d.resize(n + 5);
        ptr.resize(n + 5);
    }

    void addEdge(int u, int v, int c){
        g[u].pb(v);
        g[v].pb(u);
        Ed[u][v] = Edge(0, c);
        Ed[v][u] = Edge(0, 0);
    }

    bool bfs(){
        for(int i=1; i<=n; ++i) d[i] = -1;

        d[s] = 0;
        queue<int> q;
        q.emplace(s);

        while(q.size()){
            int u = q.front(); q.pop();
            for(int v:g[u]){
                auto [f, c] = Ed[u][v];
                if(d[v] != -1 || f == c) continue;
                d[v] = d[u] + 1;
                q.emplace(v);
            }
        }

        return d[t] != -1;
    }

    int dfs(int u, int cur = INF){
        if(cur == 0 || u == t) return cur;
        for(int &id=ptr[u]; id<sz(g[u]); ++id){
            int v = g[u][id];
            auto [f, c] = Ed[u][v];
            if(d[v] != d[u] + 1 || f == c) continue;

            int delta = dfs(v, min(cur, c - f));
            if(!delta) continue;
            Ed[u][v].f += delta;
            Ed[v][u].f -= delta;
            return delta;
        }
        return 0;
    }

    long long flow(){
        long long ansFlow = 0;
        while(bfs()){
            for(int i=1; i<=n; ++i) ptr[i] = 0;
            while(int curFlow = dfs(s)){
                ansFlow += curFlow;
            }
        }
        return ansFlow;
    }
};
