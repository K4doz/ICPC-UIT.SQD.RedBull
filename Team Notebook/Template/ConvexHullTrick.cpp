struct Line{
    ll a, b;

    Line() = default;
    Line(ll _a, ll _b){
        a = _a;
        b = _b;
    }

    ll val(ll x){
        return a * x + b;
    }
};

struct CHT{
    deque<Line> q;

    bool better(Line a, Line b, Line c){
        return (b.b - a.b) * (a.a - c.a) >= (c.b - a.b) * (a.a - b.a);
    }

    void add(Line cur){
        while(q.size() > 1 && better(q[sz(q)-2], q.back(), cur)){
            q.pop_back();
        }
        q.pb(cur);
    }

    ll get(ll x){
        while(q.size() > 1 && q.front().val(x) > q[1].val(x)){
            q.pop_front();
        }
        return q.front().val(x);
    }
};
