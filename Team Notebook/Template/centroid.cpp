int sz[N], par[N], del[N];
vector<int> g[N];

void dfs_sz(int u, int p = -1){
    sz[u] = 1;
    for(int v:g[u]) if(v != p){
        dfs_sz(v, u);
        sz[u] += sz[v];
    }
}

int centroid(int u, int p, int n){
    for(int v:g[u]) if(v != p && !del[v] && sz[v] > n/2){
        return centroid(v, u, n);
    }
    return u;
}

void cd(int u, int p = -1){
    dfs_sz(u);
    u = centroid(u, p, sz[u]);

    par[u] = p;
    del[u] = 1;

    for(int v:g[u]) if(v != p && !del[v]) cd(v, u);
}