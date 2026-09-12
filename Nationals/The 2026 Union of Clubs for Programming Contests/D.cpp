/*
    Author: Cadocx
    Codeforces: https://codeforces.com/profile/Kadoc
    VNOJ: oj.vnoi.info/user/Cadoc
*/

#include <bits/stdc++.h>
using namespace std;

// input/output
#define fastIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define el cout << '\n'
#define debug(x) cout << #x << " = " << x << '\n'
#define execute cerr << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << "s"
// #pragma GCC optimize("O2", "unroll-loops", "Ofast")
// #pragma GCC target("avx,avx2,fma")
//data type
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define piv pair<int, vector<int>>
#define vi vector<int>
#define vl vector<ll>
#define vc vector<char>
template<typename T> bool maximize(T &res, const T &val) { if (res < val){ res = val; return 1; }; return 0; }
template<typename T> bool minimize(T &res, const T &val) { if (res > val){ res = val; return 1; }; return 0; }
//STL
#define sz(x) (int)(x).size()
#define FOR(i,l,r) for(auto i = l; i <= r; i++)
#define FORD(i,r,l) for(auto i = r; i >= l; i--)
#define forin(i,a) for(auto i : a)
#define pb push_back
#define eb emplace_back
#define pf push_front
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
//bitmask
#define bitcnt(n) __builtin_popcount(n)
#define MASK(i) (1 << (i))
#define bit(n, i) (((n) >> (i)) & 1)
#define set_on(n, i) ((n) | mask(i))
#define set_off(n, i) ((n) & ~mask(i))
//constant
#define N 200005
#define MOD 998244353
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 0

int n;
int sz[N], h[N];
vector<int> g[N];
ll Ans[N];

ll pw(int a, int b){
    if(a == 0) return 1;
    if(a == 1) return a % MOD;
    ll t = pw(a, b/2); t = t % MOD * t % MOD;
    if(b&1) return a % MOD * t % MOD;
    return t;
}

void dfs(int u, int p = -1){
    sz[u] = 1;
    for(int v:g[u]) if(v != p){
        h[v] = h[u] + 1;
        dfs(v, u);
        sz[u] += sz[v];
    }
    Ans[u] = (1 + h[u] + 1ll * (n - sz[u] - h[u]) * 499122177 % MOD) % MOD;
}

void solve(){
    cin >> n;
    for(int i=1; i<n; ++i){
        int u, v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1);
    for(int i=1; i<=n; ++i) cout << Ans[i], el;
}

int main(){
    #define NAME "TASK"
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    fastIO;
    
    if(Kadoc){
        int tc; cin >> tc;
        while(tc--){
            solve();
        }
    } else solve();
}s