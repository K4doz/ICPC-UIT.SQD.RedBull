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
#define Kadoc 0

ll w, h, d, n;
vector<ll> Q1, Q2, Q3;

bool Check(ll u, ll v, ll x) {

    if (n % u != 0) return false;

    if (n % v != 0) return false;

    if (n % x != 0) return false;

    if (u * v > n) return false;

    if (v * x > n) return false;

    if (u * x > n) return false;

    if (n  == (u * v * x)) return true;

    return false;

}

void solve(){
    cin >> w >> h >> d >> n;


    for (ll i = 1; i * i <= w; i++)
        if (w % i == 0) {
            Q1.push_back(i);
            Q1.push_back(w / i);
        }

     for (ll i = 1; i * i <= h; i++)
        if (h % i == 0) {
            Q2.push_back(i);
            Q2.push_back(h / i);
        }
     for (ll i = 1; i * i <= d; i++)
        if (d % i == 0) {
            Q3.push_back(i);
            Q3.push_back(d / i);
        }


    for (ll u : Q1)
        for (ll v : Q2)
                for(ll x : Q3)
                    if (Check(u, v, x)) {

                        cout << u - 1 << " " << v - 1 << " " << x - 1;
                        return;
                    }

    cout << -1;
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
            cout << endl;
        }
    } else solve();
}