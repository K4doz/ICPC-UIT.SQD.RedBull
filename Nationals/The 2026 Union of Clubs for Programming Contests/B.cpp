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

int n;

bool kt(int a, int b, int n){
    int A = (n + 1) / 2, B = n / 2;
    ll sum = ((A * a % 11 - B * b % 11) % 11 + 11) % 11;

    // if(a == 3 && b == 6 && n == 15) {cout << a << ' ' << b << ' ' << sum; el;}

    // giam sum: a giam sum, b tang sum
    // tang 11 - sum: a tang sum, b giam sum

    if(a - sum >= 0) return 0;
    if(b + sum <= 9) return 0;

    if(a + 11 - sum <= 9) return 0;
    if(b - 11 + sum >= 0) return 0;

    //cout << a << " " << b << " " << n << "\n";
    return 1;
}

bool check(string n){
    if(sz(n) < 3) return 0;

    vector<int> mark(10, 0);
    
    for(int i=0; i+2<sz(n); i++){
        if(n[i] != n[i+2]) return 0;
        if(n[i] == n[i+1]) return 0;
    }

    return kt(n[0] - '0', n[1] - '0', sz(n));
}

ll calc(string s){
    int n = sz(s);
    for(char c:s){
        if(c != '0') break;
        n--;
    }

    ll Ans = 0;
    for(int i=1; i<n; ++i){
        for(int a=1; a<10; ++a){
            for(int b=0; b<10; ++b) if(a != b){
                Ans += kt(a, b, i);
            }
        }
    }

    //cout << kt(1, 2, 2) << "\n";

    // bang nhau
    for(int a=1; a<10; ++a){
        for(int b=0; b<10; ++b) if(a != b){
            int type = 0;
            //0 be hon hoac bang
            //2 lon hon

            for(int i=0; i < n; i++){
                if(i % 2 == 0){
                    if(s[i] - '0' == a) continue;
                    if(a > s[i] - '0') type = 1;
                    break;
                }
                else{
                    if(s[i] - '0' == b) continue;
                    if(b > s[i] - '0') type = 1;
                    break;
                }
            }

            if(type == 0)
                Ans += kt(a, b, n);
        }
    }

    return Ans;
}

void solve(){
    string L, R; cin >> L >> R;
    //cout << kt(1, 2, 2);
    cout << calc(R) - calc(L) + check(L);
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