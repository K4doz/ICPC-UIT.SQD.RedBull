int sz[N], par[N], h[N];
int head[N], pos[N], Timer = 0;
vector<int> g[N];

void dfs_sz(int u){
    sz[u] = 1;
    for(int v:g[u]) if(v != par[u]){
        h[v] = h[u] + 1;
        par[v] = u;
        dfs_sz(v);
        sz[u] += sz[v];
    }
}

void hld(int u, int p){
    head[u] = p;
    pos[u] = ++Timer;

    int bigC = -1;
    for(int v:g[u]) if(v != par[u]) if(bigC < 0 || sz[bigC] < sz[v]) bigC = v;

    if(bigC != -1) hld(bigC, p);
    for(int v:g[u]) if(v != par[u] && v != bigC) hld(v, v);
}

int lca(int u, int v){
    for(;head[u] != head[v]; u = par[head[u]]){
        if(h[head[u]] < h[head[v]]) swap(u, v);
    }

    if(h[u] > h[v]) swap(u, v);
    return u;
}