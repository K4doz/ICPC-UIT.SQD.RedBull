/* merge_segments.cpp
Merge some segments [l, r] (1 <= l <= r <= n) intersected to union.
*/

vector<pair<int,int>> mergeSegments(int n, const vector<pair<int,int>>& segs){
    vector<int> far(n + 2);
    iota(far.begin(), far.end(), 0);

    for(auto [l, r] : segs) far[l] = max(far[l], r);

    vector<pair<int,int>> Ans;
    for(int i = 1; i <= n; ++i){
        int r = far[i];
        for(int j = i; j <= r; ++j) r = max(r, far[j]);
        Ans.emplace_back(i, r);
        i = r;
    }
    
    return Ans;
}