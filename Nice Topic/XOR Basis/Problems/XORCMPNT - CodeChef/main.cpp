// https://www.codechef.com/problems/XORCMPNT

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(), x.end()
#define Kadoc 1

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll Rand(ll l, ll r){
	assert(l <= r);
	return rng() * rng() % (r - l + 1);
}

int n, k, m;

struct Basis{
	vector<int> basis;

	Basis() = default;

	void insert(int x){
		for(auto val:basis) x = min(x, x ^ val);
		if(x != 0) basis.push_back(x);
	}
};

void Solve(){
	cin >> k >> m;
	Basis T;
	for(int i=1; i<=m; ++i){
		int x; cin >> x;
		T.insert(x);
	}

	int n = T.basis.size();
	cout << (1 << (k - n)) << '\n';
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	#define NAME "main"
	if(fopen(NAME".inp", "r")){
		freopen(NAME".inp", "r", stdin);
		freopen(NAME".out", "w", stdout);
	}

	int T = 1;
	if(Kadoc) cin >> T;
	while(T--){
		Solve();
	}

	return 0;
}