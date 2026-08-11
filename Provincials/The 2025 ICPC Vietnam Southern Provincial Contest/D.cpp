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
#define pii pair<ll, int>
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
#define N 100005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 0

ll n;
int k;
pii a[N];
ll dp[55][10005], sdp[55][10005], inv[55];

ll pw(ll a, int b){
    if(b == 0) return 1;
    if(b == 1) return a % MOD;
    ll t = pw(a, b/2); t = t % MOD * t % MOD;
    if(b&1) return a % MOD * t % MOD;
    return t;
}

void add(ll &a, ll b){
    a += b;
    if(a >= MOD) a -= MOD;
    if(a < 0) a += MOD;
}

void solve(){
    cin >> n >> k;

    int m = 0;
    for(int i=2; 1ll*i*i<=n; ++i){
        if(n % i != 0) continue;

        a[++m].fi = i;
        while(n % i == 0) a[m].se++, n /= i;
    }
    if(n > 1) a[++m] = pii(n, 1);

    for(int i=1; i<=51; ++i) inv[i] = pw(i, MOD - 2);

    ll Ans = 1;
    for(int i=1; i<=m; ++i){
        auto [p, q] = a[i];

        for(int x=0; x<=50; ++x){
            for(int j=0; j<=k; ++j){
                dp[x][j] = sdp[x][j] = 0;
            }
        }

        dp[q][0] = 1;
        for(int x=0; x<=q; ++x) sdp[x][0] = inv[q+1];
        for(int j=1; j<=k; ++j){
            for(int x=q; x>=0; --x){
                add(dp[x][j], sdp[x][j-1]);
                add(sdp[x][j], sdp[x+1][j]);
                add(sdp[x][j], dp[x][j] * inv[x+1] % MOD);
            }
        }

        ll Tot = 0;
        for(int x=0; x<=q; ++x) add(Tot, dp[x][k] * pw(p, x) % MOD);

        Ans = Ans * Tot % MOD;
    }

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