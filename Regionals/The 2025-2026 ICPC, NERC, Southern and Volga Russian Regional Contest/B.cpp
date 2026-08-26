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
#define N 200005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 1

int n, curQuarter;
int cnt[N];

struct Point{
    int x, y;
    bool operator < (const Point &b) const{
        ll A = 1ll * y * b.x - 1ll * b.y * x;
        return (A < 0 || (A == 0 && y < b.y));
    }
    bool operator == (const Point &b) const{
        return pii(x, y) == pii(b.x, b.y);
    }
} p[N], v[N];

bool ccw(Point AB, Point AC){
    return 1ll * AB.x * AC.y - 1ll * AB.y * AC.x > 0;
}

bool ccw(Point A, Point B, Point C){
    return 1ll * (B.x - A.x) * (C.y - A.y) - 1ll * (B.y - A.y) * (C.x - A.x) > 0;
}

bool cw(Point AB, Point AC){
    return 1ll * AB.x * AC.y - 1ll * AB.y * AC.x < 0;
}

bool cw(Point A, Point B, Point C){
    return 1ll * (B.x - A.x) * (C.y - A.y) - 1ll * (B.y - A.y) * (C.x - A.x) < 0;
}

int getQuarter(Point P){
    auto [x, y] = P;
    if(x > 0 && y >= 0) return 0;
    if(x >= 0 && y < 0) return 1;
    if(x < 0 && y <= 0) return 2;
    return 3;
}

bool convexClosure(int l, int r){
    if(curQuarter > 4) return 0;
    if(curQuarter < 4) return 1;
    return ccw(v[l], v[r-1]);
}

void solve(){
    cin >> n;
    for(int i=1; i<=n; ++i){
        cin >> p[i].x >> p[i].y;
    }

    for(int i=1; i<n; ++i) v[i] = {p[i+1].x - p[i].x, p[i+1].y - p[i].y};
    for(int i=1; i<n-1; ++i) cnt[i] = (getQuarter(v[i+1]) - getQuarter(v[i]) + 4) % 4;

    int Ans = 0;
    curQuarter = 0;
    for(int l=1, r=3; r<=n; ++r){
        if(!cw(v[r-2], v[r-1])){
            l = r-1;
            curQuarter = 0;
            continue;
        }

        curQuarter += cnt[r-2];
        while(r-l+1 >= 3){
            bool ok = 1;
            if(!cw(p[r-2], p[r-1], p[r])) ok = 0;
            if(!cw(p[r-1], p[r], p[l])) ok = 0;
            if(!cw(p[r], p[l], p[l+1])) ok = 0;
            if(!convexClosure(l, r)) ok = 0;

            if(!ok) curQuarter -= cnt[l++];
            else break;
        }

        if(r-l+1 >= 3) Ans = max(Ans, r-l+1);
        // cout << l << ' ' << r; el;
    }

    cout << Ans; el;
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