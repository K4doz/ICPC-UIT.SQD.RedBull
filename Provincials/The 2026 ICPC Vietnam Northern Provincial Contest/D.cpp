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
#define pii pair<ll, int>
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

int n, C;
int a[N];
ll pre[N], suf[N];
ll pw[44];

int Cal(ll x){
    if(x == 1) return 0;
    return 64 - __builtin_clzll(x-1);
}

void solve(){
    cin >> C >> n;
    for(int i=1; i<=n; ++i) cin >> a[i];

    pw[1] = 1;
    for(int i=2; i<=40; ++i) pw[i] = pw[i-1] * 2ll;

    // k: pre[i] - 2^k <= pre[j-1] < pre[i] - 2^(k-1)
    if(C == 1){
        int x; cin >> x;

        ll Sum = 0;
        int Ans = 0;
        for(int i=x; i>=1; --i){
            Sum += a[i];
            Ans += Cal(Sum) + 1;
        }

        Sum = 0;
        for(int i=x+1; i<=n; ++i){
            Sum += a[i];
            Ans += Cal(Sum) + 1;
        }

        cout << Ans;
    }
    else{
        ll Sum = 0;
        vector<pii> V;
        V.emplace_back(0, 0);
        for(int i=1; i<=n; ++i){
            Sum += a[i];

            for(int k=1; k<=40; ++k){
                auto itL = lower_bound(all(V), pii(Sum - pw[k], -1));
                auto itR = lower_bound(all(V), pii(Sum - pw[k-1], -1));

                if(itL != V.end() && itR != V.begin()){
                    itR--;
                    pre[i] += 1ll * k * ((*itR).se - (*itL).se + 1);
                }
            }

            V.emplace_back(Sum, i);
        }

        Sum = 0;
        V.clear();
        V.emplace_back(0, 0);
        for(int i=n; i>=1; --i){
            Sum += a[i];

            for(int k=1; k<=40; ++k){
                auto itL = lower_bound(all(V), pii(Sum - pw[k], -1));
                auto itR = lower_bound(all(V), pii(Sum - pw[k-1], -1));

                if(itL != V.end() && itR != V.begin()){
                    itR--;
                    suf[i] += 1ll * k * ((*itR).se - (*itL).se + 1);
                }
            }

            V.emplace_back(Sum, n-i+1);
        }

        int Ans = -1;
        ll Best = LINF;
        for(int i=1; i<=n; ++i){
            if(Best > pre[i] + suf[i+1]){
                Best = pre[i] + suf[i+1];
                Ans = i;
            }
        }

        cout << Ans;
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