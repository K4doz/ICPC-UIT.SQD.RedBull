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

int n, k;
int cnt[105];
double C[33][33];

void solve(){
    cin >> n >> k;
    FOR(i, 1, n){
        int x; cin >> x;
        cnt[x]++;
    }

    // p(a, b) = sum(p^(a+1) * q^b) / sum(p^a * q^b)
    // A = C(a+1, b) * p(a, b)
    // B = C(a, b+1) * (1 - p(a, b))
    // C(a, b) = max(A + B, 2A)

    for(int a=k; a>=0; --a){
        for(int b=k-a; b>=0; --b){
            if(a + b == k){
                C[a][b] = 1;
                continue;
            }

            double top = 0, bot = 0;
            for(int i=0; i<=100; ++i){
                if(!cnt[i]) continue;

                double f = 1.0 * i / 100;
                top += pow(f, a+1) * pow(1-f, b) * cnt[i];
                bot += pow(f, a) * pow(1-f, b) * cnt[i];
            }

            if(bot == 0) continue;

            double p = top / bot;
            double A = C[a+1][b] * p;
            double B = C[a][b+1] * (1 - p);

            C[a][b] = max(A + B, 2.0 * A);
        }
    }

    cout << fixed << setprecision(20) << 1000 * C[0][0] - 1000 << '\n';
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