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

int n, m;

void solve(){
    string op; cin >> op;
    if(op[0] == 'f'){
        string s; cin >> n >> s;
        vector<int> f(11, 0);

        s = ' ' + s;

        int Tot = 0;
        int sTot = 0;
        for(int i=1; i<=n; ++i){
            for(int j=0; j<=10; ++j) if(i>>j&1){
                f[j] ^= (s[i] == '1');
            }
            sTot ^= (s[i] == '1');
            Tot ^= (s[i] == '1');
        }

        int fTot = 0;
        for(int i=0; i<=10; ++i){
            cout << f[i];
            fTot ^= f[i];
            Tot ^= f[i];
        }
        cout << fTot;
        for(int i=1; i<=n; ++i) cout << s[i];
        cout << sTot;
        Tot ^= (sTot ^ fTot);
        cout << Tot;
        cout << '\n';
    }
    else{
        string t; cin >> n >> t;
        m = t.size();
        string s = "";
        for(int i=12; i<m-2; ++i) s += t[i];

        s = ' ' + s;
        vector<int> f(11, 0);

        int Tot = 0;
        int sTot = 0;
        for(int i=1; i<=n; ++i){
            for(int j=0; j<=10; ++j) if(i>>j&1){
                f[j] ^= (s[i] == '1');
            }
            sTot ^= (s[i] == '1');
            Tot ^= (s[i] == '1');
        }

        int fTot = 0;
        for(int i=0; i<=10; ++i){
            fTot ^= (t[i] - '0');
            Tot ^= (t[i] - '0');
        }
        Tot ^= ((t[m - 2] - '0') ^ (t[11] - '0'));

        if(Tot != (t[m - 1] - '0')){
            cout << 1 << '\n';

            if(sTot != (t[m - 2] - '0')){
                int pos = 0;
                for(int i=0; i<=10; ++i) if(f[i] != (t[i] - '0')){
                    pos += (1<<i);
                }

                if(pos != 0 && pos <= n){
                    s[pos] = (s[pos] == '1'? '0' : '1');
                }
            }

            for(int i=1; i<=n; ++i) cout << s[i];
        }
        else{
            int pos = 0;
            for(int i=0; i<=10; ++i) if((t[i] - '0') != f[i]){
                pos |= (1<<i);
            }

            if(pos != 0){
                cout << 2 << '\n';
            }
            else{
                cout << 0 << '\n';
                for(int i=1; i<=n; ++i) cout << s[i];
                cout << '\n';
            }
        }
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
