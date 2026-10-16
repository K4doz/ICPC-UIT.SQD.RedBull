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
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 0

const int nMax = 2e5;

int n, root = 0;
int sz[N], dp[N];
int Ans = INF;

void dfs(int u){
    if(u != 0 && u * 2 <= nMax){
        dfs(u * 2);
        sz[u] += sz[u * 2];
        dp[u] += dp[u * 2] + sz[u * 2];
    }

    if(u * 2 + 1 <= nMax){
        dfs(u * 2 + 1);
        sz[u] += sz[u * 2 + 1];
        dp[u] += dp[u * 2 + 1] + sz[u * 2 + 1];
    }

    if(root == 0 && sz[u] == n) root = u;
}

void Cal(int u){
    Ans = min(Ans, dp[u]);

    if(u * 2 + 1 <= nMax){
        int v = u * 2 + 1;
        dp[v] += dp[u] - (dp[v] + sz[v]) + (n - sz[v]);
        Cal(u * 2 + 1);
    }
}

void solve(){
    cin >> n;
    for(int i=1; i<=n; ++i){
        int x; cin >> x;
        sz[x]++;
    }

    dfs(0);
    Cal(root);

    cout << Ans;
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
}