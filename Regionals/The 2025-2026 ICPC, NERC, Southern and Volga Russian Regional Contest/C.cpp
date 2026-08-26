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
#define N 6005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define base 31
#define Kadoc 1

int dx[] = {0, 0, 1};
int dy[] = {-1, 1, 0};


int n;
char s[N];
int dp[N][N][2];


int Calc(int l, int r, int state) {


    if (dp[l][r][state] != dp[0][0][0]) return dp[l][r][state];

    if (l == r) {

        if (s[l] == '(')
        dp[l][r][state] = 1;
        else dp[l][r][state] = -1;
    }
    else if (state == 0) {

        int left = Calc(l + 1, r, 1);

        int right = Calc(l, r - 1, 1);

        dp[l][r][state] = max(left, right);
    }
    else if (state == 1) {
        int left = 0;

        if (s[l] == '(') left++;
        else left--;

        int right = 0;

        if (s[r] == '(') right++;
        else right--;

        left = min(left, left + Calc(l + 1, r, 0));

        right = min(right, right + Calc(l, r - 1, 0));

        dp[l][r][state] = min(left, right);
    }

  //  cout << l << " " << r << " " << state << " " << dp[l][r][state] << endl;

    return dp[l][r][state];
}

void solve(){

    
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= 1; k++)
                dp[i][j][k] = INF;

   // cout << dp[0][0][0] << endl;

    if (s[1] == '(' && Calc(2, n, 0) <= -1) cout << "Monocarp";
    else if (s[n] == '(' && Calc(1, n - 1, 0) <= -1) cout << "Monocarp";
    else cout << "Polycarp";

    cout << endl;
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