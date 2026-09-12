struct Point{
    int x, y;

    Point() = default;
    Point(int _x, int _y){
        x = _x;
        y = _y;
    }

    bool operator < (const Point &b) const{
        return pii(x, y) < pii(b.x, b.y);
    }

    bool operator == (const Point &b) const{
        return pii(x, y) == pii(b.x, b.y);
    }
};

ll cross(Point a, Point b, Point c){
    Point AB = Point(b.x - a.x, b.y - a.y);
    Point AC = Point(c.x - a.x, b.y - a.y);
    return 1ll * AB.x * AC.y - 1ll * AC.x * AB.y;
}

bool ccw(Point a, Point b, Point c){
    Point AB = Point(b.x - a.x, b.y - a.y);
    Point AC = Point(c.x - a.x, b.y - a.y);
    return 1ll * AB.x * AC.y - 1ll * AC.x * AB.y > 0;
}

vector<Point> buildConvexHull(vector<Point> &a){
    sort(all(a));

    vector<Point> h;

    int n = sz(a);
    for(int i=0; i<n; ++i){
        while(h.size() > 1 && ccw(h[sz(h) - 2], h.back(), a[i])){
            h.pop_back();
        }
        h.pb(a[i]);
    }

    for(int i=n-1; i>=0; --i){
        while(h.size() > 1 && ccw(h[sz(h) - 2], h.back(), a[i])){
            h.pop_back();
        }
        h.pb(a[i]);
    }

    if(n > 1) h.pop_back();

    return h;
}
