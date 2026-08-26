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
#define N 10005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 0

int n, k, m;
vector<int> g[33][N];
int Ans[N];

struct Query{
    int l, r, x;
} p[N];

struct StoerWagner{
    int numVertices;
    vector<vector<int>> mat;

    StoerWagner(int n) : numVertices(n + 1), mat(n + 1, vector<int>(n + 1, 0)) {}

    void addEdge(int u, int v, int w = 1) {
        if (u != v && u < numVertices && v < numVertices) {
            mat[u][v] += w;
            mat[v][u] += w;
        }
    }

    void buildFromAdj(const vector<int> adj[]) {
        for (int u = 0; u < numVertices; ++u) {
            for (int v : adj[u]) {
                if (u < v && v < numVertices) {
                    mat[u][v]++;
                    mat[v][u]++;
                }
            }
        }
    }

    int minCut(vector<int> &cutS, vector<int> &cutT) {
        vector<int> v(numVertices);
        iota(v.begin(), v.end(), 0);

        vector<vector<int>> group(numVertices);
        for (int i = 0; i < numVertices; ++i) group[i] = {i};

        int ans = INF;
        vector<int> bestPartition;
        int curN = numVertices;

        while (curN > 1) {
            vector<int> w(curN, 0);
            vector<bool> added(curN, false);
            int prev = -1, last = -1;

            for (int step = 0; step < curN; ++step) {
                int sel = -1;
                for (int i = 0; i < curN; ++i) {
                    if (!added[i] && (sel == -1 || w[i] > w[sel])) {
                        sel = i;
                    }
                }
                added[sel] = true;
                prev = last;
                last = sel;
                for (int i = 0; i < curN; ++i) {
                    if (!added[i]) {
                        w[i] += mat[v[sel]][v[i]];
                    }
                }
            }

            if (w[last] < ans) {
                ans = w[last];
                bestPartition = group[v[last]];
            }

            int uLast = v[last], uPrev = v[prev];
            for (int i = 0; i < curN; ++i) {
                if (i != prev && i != last) {
                    mat[uPrev][v[i]] += mat[uLast][v[i]];
                    mat[v[i]][uPrev] += mat[v[i]][uLast];
                }
            }

            group[uPrev].insert(group[uPrev].end(), group[uLast].begin(), group[uLast].end());

            v.erase(v.begin() + last);
            curN--;
        }

        cutS = bestPartition;
        vector<bool> inS(numVertices, false);
        for (int u : cutS) inS[u] = true;
        cutT.clear();
        for (int i = 0; i < numVertices; ++i) {
            if (!inS[i]) cutT.push_back(i);
        }

        return (ans == INF ? 0 : ans);
    }

    int minCut() {
        vector<int> S, T;
        return minCut(S, T);
    }

    pair<vector<int>, vector<int>> getCutByRoot(int root = 0) {
        vector<int> S, T;
        minCut(S, T);
        bool rootInS = (find(all(S), root) != S.end());
        if (rootInS) return {S, T};
        return {T, S};
    }

    vector<int> getAssignment(int root = 0) {
        vector<int> S, T;
        minCut(S, T);
        vector<int> val(numVertices, 0);
        bool rootInS = (find(all(S), root) != S.end());
        for (int u : (rootInS ? T : S)) {
            val[u] = 1;
        }
        return val;
    }
};

void solve(){
    cin >> n >> k >> m;
    for(int i=1; i<=m; ++i){
        int l, r, x; cin >> l >> r >> x;
        p[i] = {l, r, x};
        for(int j=29; j>=0; --j){
            if(!(x>>j&1)) continue;
            g[j][r].pb(l-1);
            g[j][l-1].pb(r);
        }
    }

    // voi moi bit j: ta can tinh k - cnt, voi cnt la so luong term bat bit j trong m term
    // (pre[r] ^ pre[l-1]) & x:
        // neu x = 0: chac chan term do = 0
        // neu x = 1: term = 1 neu pre[r] != pre[l-1]
    // -> x = 1 thi tao canh giua node r va node l-1
    // can chia n+1 dinh (0 -> n) thanh 2 tap 0 va 1 sao cho so canh tu tap 0 -> tap 1 la nho nhat
    // -> tim lat cat cuc tieu cua do thi tai bit j
    // truy vet: pre[0] = 0 -> phu thuoc vao viec pre[0] nam o tap nao de ta xac dinh duoc gia tri

    for(int j=29; j>=0; --j){
        StoerWagner sw(n);
        sw.buildFromAdj(g[j]);

        vector<int> cutS, cutT;
        int minCutVal = sw.minCut(cutS, cutT);
        if(k <= minCutVal) continue;

        vector<int> bitVal(n + 1, 0);
        bool rootInS = (find(all(cutS), 0) != cutS.end());
        for (int u : (rootInS ? cutT : cutS)) {
            bitVal[u] = 1;
        }

        for(int i=1; i<=n; ++i){
            Ans[i] |= ((bitVal[i] ^ bitVal[i-1])<<j);
        }
    }

    for(int i=1; i<=n; ++i) cout << Ans[i] << ' ';
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