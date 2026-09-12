void add(ll &a, ll b){
    a += b;
    if(a >= MOD) a -= MOD;
    if(a < 0) a += MOD;
}

struct Matrix{
    vector<vector<ll>> val;

    int row(){
        return val.size() - 5;
    }

    int col(){
        return val[0].size() - 5;
    }

    vector<ll> & operator [] (int i){
        return val[i];
    }

    Matrix() = default;
    Matrix(int n, int m){
        val.resize(n+5, vector<ll>(m+5, 0));
    }
    static Matrix identity(int n){
        Matrix a(n, n);
        FOR(i, 1, n) a[i][i] = 1;
        return a;
    }

    Matrix operator * (Matrix &b){
        Matrix a = *this;
        int m = a.row(), n = a.col(), p = b.col();
        Matrix c(m, p);

        FOR(i, 1, m){
            FOR(j, 1, p){
                FOR(k, 1, n){
                    add(c[i][j], a[i][k] * b[k][j] % MOD);
                }
            }
        }

        return c;
    }

    Matrix pw(ll n){
        Matrix a = *this;
        Matrix Ans = identity(a.row());

        int k = 63 - __builtin_clzll(n);
        FOR(i, 0, k){
            if(n>>i&1ll) Ans = Ans * a;
            a = a * a;
        }
        return Ans;
    }
};