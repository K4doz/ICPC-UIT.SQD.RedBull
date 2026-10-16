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
#define N 100005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 1

int n;
ll K;

ll Cal(ll row, ll pos){
    ll X = (1<<pos)-1, Y = (1<<(pos-1));
    return 1ll * (row + 1) / 2 * X + 1ll * row / 2 * Y;
}

void solve(){
    cin >> n >> K;

    ll pos = 1;
    for(; (1<<pos) <= (1<<n); ++pos){
        ll num = 1ll * ((1<<pos)-1) * ((1<<pos)-1);
        if(num >= K) break;
    }

    K -= 1ll * ((1<<(pos-1))-1) * ((1<<(pos-1))-1);

    ll l = 1, r = ((1<<pos)-1), row = r;
    while(l <= r){
        ll m = (l+r)>>1;
        if(Cal(m, pos) >= K) r = m-1, row = m;
        else l = m+1;
    }

    K -= Cal(row-1, pos);

    ll col = (1<<(n-pos));
    if(row&1) col += 1ll * (K - 1) * (1<<(n-pos));
    else col += 1ll * (K - 1) * (1<<(n-pos+1));
    row *= (1<<(n-pos));

    cout << row << ' ' << col; el;
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