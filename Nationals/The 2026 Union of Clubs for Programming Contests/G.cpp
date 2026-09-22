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
#define N 300005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 0

int n, q;

struct Vector{
    int x, y;

    Vector() = default;
    Vector(int _x, int _y): x(_x), y(_y){}

    int angle(){
        if(x == 0 && y == 0) return 4;
        if(x > 0 && y >= 0) return 0;
        if(x <= 0 && y > 0) return 1;
        if(x < 0 && y <= 0) return 2;
        return 3;
    }

    bool equalToZero(){
        return pii(x, y) == pii(0, 0);
    }

    bool operator < (Vector &b) const{
        Vector a = *this;
        if(a.angle() != b.angle()) return a.angle() < b.angle();
        if(x == 0 && b.x == 0) return y < b.y;
        if(x != 0 && b.x == 0) return a.angle() % 2 == 0;
        if(x == 0  && b.x != 0) return a.angle() % 2 == 1;

        return 1ll * y * b.x < 1ll * x * b.y;
    }

    bool operator == (Vector b) const{
        if(1ll * x * b.y != 1ll * b.x * y) return 0;
        return 1ll * x * b.x + 1ll * y * b.y > 0;
    }

    friend Vector operator + (Vector a, Vector b){
        return Vector(a.x + b.x, a.y + b.y);
    }

    friend Vector operator - (Vector a, Vector b){
        return Vector(a.x - b.x, a.y - b.y);
    }

    friend ostream & operator << (ostream &cout, Vector &p){
        cout << p.x << ' ' << p.y;
        return cout;
    }
} V[N];

ll cross(Vector a, Vector b){
    return 1ll * a.x * b.y - 1ll * b.x * a.y;
}

bool cw(Vector A, Vector B, Vector C){
    return cross(B - A, C - A) <= 0;
}

long double Cal1Vec(Vector V, Vector X){
    if(V.x != 0) return (long double)X.x / V.x;
    return (long double)X.y / V.y;
}

long double Cal2Vec(Vector V1, Vector V2, Vector X){
    ll Cr = cross(V1, V2);
    if(Cr == 0) return -1;
    long double t1 = (long double)cross(X, V2) / Cr;
    long double t2 = (long double)cross(V1, X) / Cr;
    if(t1 < 0 || t2 < 0) return -1;
    return t1 + t2;
}

int lowerbound(vector<Vector> &V, Vector X){
    int l = 0, r = sz(V)-1, Ans = sz(V);
    while(l <= r){
        int m = (l+r)>>1;
        if(X < V[m] || V[m] == X) r = m-1, Ans = m;
        else l = m+1;
    }
    return Ans;
}

void solve(){
    cin >> n >> q;
    Vector P;
    for(int i=1; i<=n; ++i){
        int a, b; cin >> a >> b;
        V[i] = Vector(a, b);
        P = V[i];
    }

    V[0] = Vector(0, 0);
    sort(V, V + n + 1, [&](Vector &a, Vector &b){
        return pii(a.x, a.y) < pii(b.x, b.y);
    });
    vector<Vector> hull;

    hull.emplace_back(V[0]);
    for(int i=1; i<=n; ++i){
        while(sz(hull) > 1 && cw(hull[sz(hull)-2], hull.back(), V[i])) hull.pop_back();
        hull.emplace_back(V[i]);
    }
    int lower_sz = sz(hull);
    for(int i=n-1; i>=0; i--){
        while(sz(hull) > lower_sz && cw(hull[sz(hull)-2], hull.back(), V[i])) hull.pop_back();
        hull.emplace_back(V[i]);
    }
    if(n > 1) hull.pop_back();

    sort(all(hull));
    if(hull.back().equalToZero()) hull.pop_back();

    for(int i=1; i<=q; ++i){
        int x, y; cin >> x >> y;
        Vector X = Vector(x, y);

        if(x == 0 && y == 0){
            cout << 0 << '\n';
            continue;
        }
        if(n == 1){
            if(X == P){
                long double Res = Cal1Vec(P, X);
                if(Res < 0) cout << "-1" << '\n';
                else cout << fixed << setprecision(10) << Res << '\n';
            }
            else cout << "-1" << '\n';
            continue;
        }

        int R = lowerbound(hull, X), L = R-1;

        if(R == sz(hull)) R -= sz(hull);
        if(L == -1) L += sz(hull);

        long double Ans = numeric_limits<long double>::infinity();
        if(hull[R] == X){
            long double Res = Cal1Vec(hull[R], X);
            if(Res >= 0) Ans = min(Ans, Res);
        }

        long double Res = Cal2Vec(hull[L], hull[R], X);
        if(Res >= 0) Ans = min(Ans, Res);

        if(Ans < 0 || !isfinite(Ans)) cout << "-1" << '\n';
        else cout << fixed << setprecision(10) << Ans << '\n';
    }
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