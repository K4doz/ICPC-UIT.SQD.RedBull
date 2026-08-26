/*
    Author: UIT.DemonSlayer
    NguyenThaiSon - University of Information Technology - CS18
    PhanMinhQuan - University of Information Technology - CS20
    PhungNgocNguyenDuc - University of Information Technology - CS20
*/

#include <bits/stdc++.h>
using namespace std;

// input/output
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
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
#define vii pair<int, int>
#define vi vector<int>
#define vl vector<ll>
#define vvi vector<vector<int>>
#define vvl vector<vector<ll>>
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
#define firbit(x) 63 - __builtin_clzll(x)
//constant
#define N 100005
#define MOD 1000000007
#define mod 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define oo 0x3f3f3f3f
#define base 31
#define BL 350
#define DemonSlayer 1
///bfs
const int d4x[4] = {-1, 0, 1, 0} , d4y[4] = {0, 1, 0, -1};
const int d8x[8] = {-1, -1, 0, 1, 1, 1, 0, -1}, d8y[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int la, ra, lb, rb;

bool Cal(int x){
    if(la >= ra - x + 1) return false;
    int L = la, R = max(la + 1, ra - x + 1);
    int u = lb, v = min(rb, (L + R) - lb);
    if(u >= v) return false;

    int num = min((v - u - 1) / 3, rb - v);
    int pos = (v - u - 1 - num) / 2;

    return pos + num + 1 >= x; 
}

void solve(){
    cin >> la >> ra >> lb >> rb;
    //Cal(5);

    int L = 1, R = min(ra - la, (rb - lb + 1) / 2);
    int Ans = 0;
    while(L <= R){
        int m = L + R >> 1;
        //cout << m << "\n";
        if(Cal(m)){
            Ans = m;
            L = m + 1;
        }
        else 
            R = m - 1;
    }
    cout << Ans << "\n";
}

int main(){
    #define NAME "TASK"
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }

    //srand(time(NULL));
    fastIO;
    
    if(DemonSlayer){
        int tc; cin >> tc;
        while(tc--){
            solve();
        }
    } else solve();
}