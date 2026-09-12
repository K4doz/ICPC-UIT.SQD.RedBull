vector<int> g[N];
int c[N];
int in[N], out[N], ver[N], sz[N], Timer = 0;
 
void dfs_sz(int u, int p = -1){
	in[u] = ++Timer;
	ver[Timer] = u;
 
	sz[u] = 1;
	for(int v:g[u]) if(v != p){
		dfs_sz(v, u);
		sz[u] += sz[v];
	}
 
	out[u] = Timer;
}
 
void add(int u){
	
}
 
void del(int u){
	
}
 
void dfs(int u, int p = -1, int keep = 0){
	int bigC = -1;
	for(int v:g[u]) if(v != p) if(bigC < 0 || sz[bigC] < sz[v]) bigC = v;
 
	for(int v:g[u]) if(v != p && v != bigC) dfs(v, u);
 
	if(bigC != -1) dfs(bigC, u, 1);
	
	for(int v:g[u]) if(v != p && v != bigC){
		for(int i=in[v]; i<=out[v]; ++i) add(ver[i]);
	}
 
	add(u);
 
	// Ans[u] =  
	
	if(!keep){
		for(int i=in[u]; i<=out[u]; ++i) del(ver[i]);
	}
}