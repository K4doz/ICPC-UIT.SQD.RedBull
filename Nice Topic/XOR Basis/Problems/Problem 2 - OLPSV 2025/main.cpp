/*
    https://oj.vnoi.info/problem/olp_ct25_fibseq
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
#define N 100005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define TitChiu 1

ll n, m;
ll f[66];

int msb(ll x){
    if(x == 0) return -1;
    return 63 - __builtin_clzll(x);
}

int Calc(ll x){
    if(x == 0) return 0;

    int Ans = 0;
    while(x > 0){
        int pos = upper_bound(f+1, f+60, x) - f - 1;
        while(x >= f[pos]){
            x -= f[pos];
            Ans++;
        }
    }

    return Ans;
}

struct XorBasis{
    vector<pair<ll, ll>> basis;
    vector<ll> free;

    void insert(ll x, ll msk){
        for(auto p:basis){
            if(minimize(x, x ^ p.fi)){
                msk ^= p.se;
            }
        }

        if(x != 0) basis.pb({x, msk});
        else free.pb(msk);
    }

    int get(ll n, ll m){
        ll msk = 0;
        for(auto p:basis){
            if(minimize(m, m ^ p.fi)){
                msk ^= p.se;
            }
        }

        if(m != 0) return -1;

        int Ans = INF;
        for(int i=0; i<(1<<sz(free)); ++i){
            ll cur = msk;
            for(int j=0; j<sz(free); ++j) if(i>>j&1){
                cur ^= free[j];
            }

            ll val = n;
            for(int j=0; j<=msb(cur); ++j) if(cur>>j&1){
                val -= f[j];
            }
            if(val < 0 || (val&1)) continue;
            val >>= 1;

            Ans = min(Ans, 2 * Calc(val) + __builtin_popcountll(cur));
        }

        if(Ans == INF) Ans = -1;
        return Ans;
    }
};

// msk: -> Xor = m, Sum = x
// -> can tao ra 1 mask S it nhat sao cho sum(S) = (n - x) / 2
// cost = 2 * |S| + |msk|
// can tinh nhanh voi 1 so long long x thi xac dinh duoc ngay bitmask

void solve(){
    cin >> n >> m;
    if(((n ^ m) & 1) || n < m) return cout << -1 << '\n', void();

    XorBasis T;
    for(int i=58; i>=1; --i) if(f[i] <= n){
        T.insert(f[i], 1ll<<i);
    }

    cout << T.get(n, m); el;
}

int main(){
    #define NAME "TASK"
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    fastIO;

    f[0] = f[1] = 1;
    for(int i=2; i<=60; ++i) f[i] = f[i-1] + f[i-2];
    
    if(TitChiu){
        int tc; cin >> tc;
        while(tc--){
            solve();
        }
    } else solve();
}