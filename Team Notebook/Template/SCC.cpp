int low[N], num[N], Timer = 0, SCC = 0;
stack<int> s;
vector<int> g[N];

void tarjan(int u){
    s.push(u);
    low[u] = num[u] = ++Timer;
    for(int v:g[u]){
        if(num[v]) low[u] = min(low[u], num[v]);
        else{
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
    }

    if(low[u] == num[u]){
        SCC++;
        int v = -1;
        do{
            v = s.top();
            num[v] = n+1;
            s.pop();
        } while(v != u);
    }
}