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