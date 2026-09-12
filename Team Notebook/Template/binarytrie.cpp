struct Trie{
    vector<int> child[2];

    Trie() = default;
    Trie(int n){
        child[0].resize(n+5, 0);
        child[1].resize(n+5, 0);
    }

    int root = 1, cnt = 1;

    void add(int x){
        int u = root;
        FORD(i, 31, 0){
            int k = x>>i&1;
            if(!child[k][u]) child[k][u] = ++cnt;
            u = child[k][u];
        }
    }

    int get(int x){
        int u = root;
        int Ans = 0;
        FORD(i, 31, 0){
            int k = x>>i&1;
            if(child[k][u]) u = child[k][u];
            else{
                Ans |= (1<<i);
                u = child[1^k][u];
            }
        }

        return Ans;
    }
};