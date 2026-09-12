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
#define N 3000005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 0

int n;
string s;
bool dp[N][3][3];

int get(char x){
    if(x == 'B') return 0;
    if(x == 'L') return 1;
    return 2;
}

int add(int a, int b){
    a += b;
    if(a >= 3) a -= 3;
    if(a < 0) a += 3;
    return a;
}

void solve(){
    cin >> n >> s;

    dp[3*n][0][2] = 1;
    for(int i=3*n; i>=0; --i){
        for(int u=0; u<3; ++u){
            for(int v=0; v<3; ++v){
                if(!dp[i][u][v]) continue;

                int x = get(s[3*n - i]);
                if(u == x){
                    dp[i-1][add(u, 1)][v] = 1;
                }
                if(v == x){
                    dp[i-1][u][add(v, -1)] = 1;
                }
            }
        }
    }

    for(int u=0; u<3; ++u){
        for(int v=0; v<3; ++v){
            if(dp[0][u][v]) return cout << "Yes", void();
        }
    }

    cout << "No";
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