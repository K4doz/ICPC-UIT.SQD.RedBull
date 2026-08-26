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

int n, m, k;
int dx[] = {0, 0, 1};
int dy[] = {-1, 1, 0};

void solve(){
    cin >> n >> m >> k;
    int val[n + 5][m + 5]{0};
    char c[n + 5][m + 5]{0};
    bool oke[n + 5][m + 5]{0}, used[n + 5]{0};
    int Ans = 0;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> c[i][j], oke[i][j] = false;


    for(int j = 1; j <= m; j++){
        int cur = n;
        for(int i = n; i >= 1; i--){
            used[i] = false;
            if(c[i][j] == 'x') cur = i - 1;
            val[i][j] = cur;
        }
    }
    

    queue<pii> qu;
    qu.push({1, 1});
    oke[1][1] = true;
    for(int i = 1; i <= k; i++)
        used[i] = true, Ans++;
    

    while(qu.size()){
        auto[x, y] = qu.front();
        qu.pop();

        for(int i = 0; i < 3; i++){
            int p = x + dx[i];
            int q = y + dy[i];
            if(p < 1 || q < 1 || p > n || q > m) continue;
            if(val[p][q] < p + k - 1) continue;
            if(oke[p][q]) continue;
            oke[p][q] = true;
            if(!used[p + k - 1]){
                used[p + k - 1] = true;
                Ans++;
            }

            qu.push({p, q});
        }
    }

    cout << Ans << "\n";
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