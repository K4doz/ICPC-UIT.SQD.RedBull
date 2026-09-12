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
#define execute cerr << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << "s"
// #pragma GCC optimize("O2", "unroll-loops", "Ofast")
// #pragma GCC target("avx,avx2,fma")
//data type
#define int128 __uint128_t
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define piv pair<int, vector<int>>
#define vi vector<int>
#define vl vector<ll>
#define vc vector<char>
//STL
#define sz(x) (int)(x).size()
#define for1(i,l,r) for(auto i = l; i <= r; i++)
#define for2(i,r,l) for(auto i = r; i >= l; i--)
#define forin(i,a) for(auto i : a)
#define pb push_back
#define eb emplace_back
#define pf push_front
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
//bitmask
#define bitcnt(n) __builtin_popcount(n)
#define mask(i) (1 << (i))
#define bit(n, i) (((n) >> (i)) & 1)
#define set_on(n, i) ((n) | mask(i))
#define set_off(n, i) ((n) & ~mask(i))
//constant
#define N 10000005
#define MOD 1000230007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 1

ll n;

ll pw(ll a, ll b, ll m){
    if(!b) return 1;
    if(b == 1) return a % m;
    ll t = pw(a, b/2, m); t = t % m * t % m;
    if(b&1) return a % m * t % m;
    return t % m;
}
 
bool test(ll a, ll n, ll k, ll m){ 
    ll t = pw(a, m, n) % n;
 
    if(t == 1 || t == n-1) return 1;
 
    for(int i=1; i<k; ++i){
        t = t % n * t % n;
        if(t == n-1) return 1;
    }
 
    return 0;
}
 
bool MillerRabin(ll n){
    static vector<int> pr = {2,3,5,7,11,13,17,19,23,29,31,37};
 
    for(int a:pr) if(n == a) return 1;
    if(n < 41) return 0;
 
    ll k = 0, m = n - 1;
    while(m % 2 == 0) k++, m /= 2;
 
    for(int a:pr) if(!test(a, n, k, m)) return 0;
 
    return 1;
}

void solve(){
    cin >> n;
    if(n <= 2) cout << "NO";
    else if(n % 2 == 0 || MillerRabin(n - 2)) cout << "YES";
    else cout << "NO";
    el;
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