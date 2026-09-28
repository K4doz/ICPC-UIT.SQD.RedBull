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
int st[N << 2], lz[N << 2], ok[N << 2];
int a[N], pre[N], Ans[N];

struct Constraints{
    int l, r, rem;
    bool operator < (const Constraints &b){
        return pii(l, r) < pii(b.l, b.r);
    }
} p[N];

int ceil(int a, int b){
    return (a + b - 1) / b;
}

void push(int id, int l, int r){
    if(!lz[id]) return;

    if(l != r){
        st[id] += lz[id];
        lz[id<<1] += lz[id];
        lz[id<<1|1] += lz[id];
    }
    else if(ok[id]) st[id] += lz[id];

    lz[id] = 0;
}

void assign(int id, int l, int r, int i, int x){
    push(id, l, r);
    if(i < l || r < i) return;
    if(l == r){
        st[id] = min(st[id], x);
        ok[id] = 1;
        lz[id] = 0;
        return;
    }
    int m = (l+r)>>1;
    assign(id<<1, l, m, i, x);
    assign(id<<1|1, m+1, r, i, x);
    st[id] = min(st[id<<1], st[id<<1|1]);
}

void upd(int id, int l, int r, int u, int v, int x){
    push(id, l, r);
    if(v < l || r < u) return;
    if(u <= l && r <= v){
        lz[id] += x;
        push(id, l, r);
        return;
    }
    int m = (l+r)>>1;
    upd(id<<1, l, m, u, v, x);
    upd(id<<1|1, m+1, r, u, v, x);
    st[id] = min(st[id<<1], st[id<<1|1]);
}

int get(int id, int l, int r, int u, int v){
    push(id, l, r);
    if(v < l || r < u) return INF;
    if(u <= l && r <= v) return st[id];
    int m = (l+r)>>1;
    return min(get(id<<1, l, m, u, v), get(id<<1|1, m+1, r, u, v));
}

void solve(){
    cin >> n >> k;
    for(int i=1; i<=n; ++i){
        cin >> a[i];

        if(a[i] < 0) Ans[i] = 0;
        else Ans[i] = 1;

        pre[i] = pre[i-1] + Ans[i];
    }

    for(int i=1; i<=k; ++i){
        int l, r, c; cin >> l >> r >> c;

        int rem = ceil(c + r - l + 1, 2);
        int Sum = pre[r] - pre[l-1];
        if(rem < 0) continue;
        if(rem > Sum) return cout << "Impossible\n", void();

        p[i] = {l, r, Sum - rem};
    }

    sort(p+1, p+k+1);

    memset(st, 0x3f, sizeof st);

    int j = 0;
    for(int i=1; i<=n; ++i) if(!a[i]){
        while(j < k && p[j+1].l <= i){
            j++;
            assign(1, 1, n, p[j].r, p[j].rem);
        }
        int Min = get(1, 1, n, i, n);

        if(Min > 0){
            Ans[i] = 0;
            upd(1, 1, n, i, n, -1);
        }
    }

    for(int i=1; i<=n; ++i) cout << (Ans[i]? 1:-1) << ' ';
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