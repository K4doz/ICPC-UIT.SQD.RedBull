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
#define N 1000005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 0

string s;
int n, d[30][15], a[N], dis[N], L[N];
vector<int> adj[N], V;

char ins(char c){
    if ('0' <= c && c <= '9')
        return char((int) (c - '0' + 1) % 10 + '0');
    return char((int) (c - 'A' + 1) % 26 + 'A');
}

void pre(){
    int kt = 2;
    int num = 4;

    int cnt = 0;
    do{
        d[kt][num] = ++cnt;
        kt = (kt - 1 + 26) % 26;
        num = (num - 1 + 10) % 10;
    }
    while(kt != 2 || num != 4);
}

void dfs(int u){
    dis[u] = d[a[u]][a[L[u]]] - 1;


    for(int v : adj[u]){
        dfs(v);

        int Now = (a[u] + d[a[v]][a[L[v]]] - 1) % 26;
        int Num = (a[L[u]] + d[a[v]][a[L[v]]] - 1) % 10;
        dis[u] = max(dis[u], dis[v] + d[Now][Num] - 1);
    }
    //cout << u << " " << dis[u] << "\n";
}


void solve(){
    pre();
    cin >> s;

    n = s.size();
    s = ' ' + s;
    stack<int> st;
    for(int i = 1; i <= n; i++){
        //cout << s[i] << "\n";
        if('0' <= s[i] && s[i] <= '9'){
            a[i] = (int) s[i] - '0';
            if(!st.size() || !d[a[st.top()]][a[i]]){
                cout << -1;
                return;
            }

            L[st.top()] = i;
            st.pop();
        }
        else{
            a[i] = s[i] - 'A';
            if(st.size())
                adj[st.top()].push_back(i);
            else 
                V.push_back(i);

            st.push(i);

            //cout << st.size() << "\n";
        }
    }   

    if(st.size()){
        cout << -1;
        return;
    }

    int Ans = 0;
    for(int v : V) dfs(v), Ans = max(Ans, dis[v]);
    cout << Ans + n / 2;
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