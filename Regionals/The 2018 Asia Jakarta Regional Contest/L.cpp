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

ll k;
int n;
string s;
int dp[66][66][2];

bool check(string &s, string &t){
    int i = 0, j = 0;
    while(i < sz(s) && j < sz(t)){
        if(s[i] <= t[j]){
            i++;
            j++;
        }
        else i++;
    }

    return j == sz(t);
}

void solve(){
    cin >> k >> s;

    string t = "";
    while(k){
        t += char((k&1ll) + '0');
        k >>= 1ll;   
    }

    if(sz(s) < sz(t)) return cout << 0, void();

    int n = sz(s), m = sz(t);
    reverse(all(t));
    s = ' ' + s;
    t = ' ' + t;

    FOR(i, 0, n) dp[i][0][0] = 1;
    FOR(i, 1, n){
        FOR(j, 1, m){
            FOR(k, 0, 1) maximize(dp[i][j][k], dp[i-1][j][k]);

            if(s[i] < t[j]){
                if(j > 1 || (j == 1 && s[i] == '1')){
                    maximize(dp[i][j][1], max(dp[i-1][j-1][0], dp[i-1][j-1][1]));
                }
            }
            else if(s[i] == t[j]){
                maximize(dp[i][j][1], dp[i-1][j-1][1]);
                maximize(dp[i][j][0], dp[i-1][j-1][0]);
            }
            else maximize(dp[i][j][1], dp[i-1][j-1][1]);
        }
    }

    cout << ((dp[n][m][0] | dp[n][m][1])? sz(s) - sz(t) : sz(s) - sz(t) + 1);


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