// merge_segments.cpp
// Nén các đoạn [l, r] (1 <= l <= r <= n) giao nhau (chung ít nhất 1 vị trí)
// thành hợp của chúng. Độ phức tạp O(n + m), không cần sắp xếp.
// Muốn gộp cả đoạn kề nhau ([1,2] và [3,4]) thì thêm cạnh phủ r -> r+1.
vector<pair<int,int>> mergeSegments(int n, const vector<pair<int,int>>& segs){
    vector<int> reach(n + 2);
    iota(reach.begin(), reach.end(), 0);          // reach[i] = i
    for(auto [l, r] : segs) reach[l] = max(reach[l], r);

    vector<pair<int,int>> res;
    for(int i = 1; i <= n; ++i){
        int r = reach[i];
        for(int j = i; j <= r; ++j) r = max(r, reach[j]);
        res.emplace_back(i, r);
        i = r;
    }
    return res;
}