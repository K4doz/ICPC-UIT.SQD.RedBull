#include<bits/stdc++.h>
using namespace std;

#define el cout << '\n'
#define FOR(i, a, b) for(int i=(a); i<=(b); ++i)
#define FORD(i, a, b) for(int i=(b); i>=(a); --i)
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x).size()
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
#define N 100005

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

ll Rand(ll l, ll r){
    assert(l <= r);
    return l + rd() * rd() % (r-l+1);
}

void MakeTest(){
    ofstream cout("TASK.inp");

    int T = 1;
    // cout << T; el;
    while(T--){

    }

    cout.close();
}

int main(){
     srand(time(NULL));

     #define NTEST 500
     FOR(i, 1, NTEST){
        MakeTest();

        system("TASK.exe");
        system("TASK_1.exe");

        if(system("fc TASK.out TASK.ans")) return cout << "Test " << i << ": WRONG!\n", 0;
        cout << "Test " << i << ": CORRECT!\n";
     }
}
