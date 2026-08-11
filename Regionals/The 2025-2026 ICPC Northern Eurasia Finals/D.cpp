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


int n, pos_R[N];
queue<int> Q[N];

void solve(){
    cin >> n;

    set<pair<int, int>> Store;

    set<pair<int, int>, greater<pair<int, int>>> Left;

    vector<pair<int, int>> V;

    for (int i = 1; i <= n; i++) {
        int num;

        cin >> num;
        int l, r, Sum = 0;
        cin >> l >> r;
        Left.insert({l, i});

        for (int j = 1; j <= num; j++) {
            int x;
            cin >> x;
            Q[i].push(x);
            Sum += x;        
            V.push_back({l + Sum, i});
        }

        pos_R[i] = r - Sum;
        Store.insert({pos_R[i], i});
    }

    sort(V.begin(), V.end());

    int Ans = 0;

    auto[u, v] = *Left.begin();

    auto[uu, vv] = *Store.begin();

  //  cout << u << " " << uu << endl;
    Ans = max(Ans, uu - u);


    for (auto[len, id] : V) {

        int gett = Q[id].front();
        Q[id].pop();

        Left.insert({len, id});

        Store.erase({pos_R[id], id});


        pos_R[id] += gett;

        Store.insert({pos_R[id], id});

        auto[u, v] = *Left.begin();

        auto[uu, vv] = *Store.begin();


        Ans = max(Ans, uu - u);

    }

    cout << Ans;
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
            cout << endl;
        }
    } else solve();
}