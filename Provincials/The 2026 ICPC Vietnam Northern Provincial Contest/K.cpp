// Test Gemini 4 Argon - just for research purpose
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>
#include <numeric>

using namespace std;

struct Point {
    double x, y, w;
};

int n, m;
vector<Point> pts;

inline double dist_sq(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return dx * dx + dy * dy;
}

inline double dist(double x1, double y1, double x2, double y2) {
    return sqrt(dist_sq(x1, y1, x2, y2));
}

double eval_cluster(const vector<int>& cluster, double cx, double cy) {
    double c = 0;
    for (int idx : cluster) {
        c += pts[idx].w * dist(cx, cy, pts[idx].x, pts[idx].y);
    }
    return c;
}

pair<double, double> weiszfeld_exact(const vector<int>& cluster, pair<double, double> start_pt, int use_start, int max_iter) {
    if (cluster.empty()) return {0.0, 0.0};
    if (cluster.size() == 1) {
        return {pts[cluster[0]].x, pts[cluster[0]].y};
    }

    double sum_wx = 0, sum_wy = 0, sum_w = 0;
    int max_w_idx = cluster[0];
    for (int idx : cluster) {
        sum_wx += pts[idx].w * pts[idx].x;
        sum_wy += pts[idx].w * pts[idx].y;
        sum_w += pts[idx].w;
        if (pts[idx].w > pts[max_w_idx].w) max_w_idx = idx;
    }

    double cx = sum_wx / sum_w;
    double cy = sum_wy / sum_w;
    double best_x = cx, best_y = cy;
    double best_c = eval_cluster(cluster, cx, cy);

    if (use_start) {
        double c_st = eval_cluster(cluster, start_pt.first, start_pt.second);
        if (c_st < best_c) {
            best_c = c_st;
            best_x = cx = start_pt.first;
            best_y = cy = start_pt.second;
        }
    }

    double c_mw = eval_cluster(cluster, pts[max_w_idx].x, pts[max_w_idx].y);
    if (c_mw < best_c) {
        best_c = c_mw;
        best_x = pts[max_w_idx].x;
        best_y = pts[max_w_idx].y;
    }

    for (int iter = 0; iter < max_iter; iter++) {
        double num_x = 0, num_y = 0, den = 0;
        double pinned_w = 0;
        double gx = 0, gy = 0;

        for (int idx : cluster) {
            double dx = cx - pts[idx].x;
            double dy = cy - pts[idx].y;
            double d = sqrt(dx * dx + dy * dy);
            if (d < 1e-8) {
                pinned_w += pts[idx].w;
            } else {
                double wd = pts[idx].w / d;
                num_x += wd * pts[idx].x;
                num_y += wd * pts[idx].y;
                den += wd;
                gx += pts[idx].w * (dx / d);
                gy += pts[idx].w * (dy / d);
            }
        }

        if (den == 0) break;

        double nx, ny;
        if (pinned_w > 0) {
            double g_norm = sqrt(gx * gx + gy * gy);
            if (g_norm <= pinned_w) {
                break;
            }
            double alpha = max(0.0, 1.0 - pinned_w / g_norm);
            nx = (1.0 - alpha) * cx + alpha * (num_x / den);
            ny = (1.0 - alpha) * cy + alpha * (num_y / den);
        } else {
            nx = num_x / den;
            ny = num_y / den;
        }

        double step_sq = dist_sq(cx, cy, nx, ny);
        cx = nx;
        cy = ny;
        if (step_sq < 1e-11) break;
    }

    double fc = eval_cluster(cluster, cx, cy);
    if (fc < best_c) {
        best_c = fc;
        best_x = cx;
        best_y = cy;
    }

    return {best_x, best_y};
}

double run_lloyd(vector<pair<double, double>>& centers, int max_iter, int weisz_iter) {
    vector<vector<int>> clusters(m);
    vector<double> d1(n);
    double prev_cost = 1e300;
    double best_cost = 1e300;
    vector<pair<double, double>> best_c = centers;

    for (int it = 0; it < max_iter; it++) {
        for (int j = 0; j < m; j++) clusters[j].clear();
        double total_cost = 0;

        for (int i = 0; i < n; i++) {
            int bj = 0;
            double bdsq = dist_sq(pts[i].x, pts[i].y, centers[0].first, centers[0].second);
            for (int j = 1; j < m; j++) {
                double dsq = dist_sq(pts[i].x, pts[i].y, centers[j].first, centers[j].second);
                if (dsq < bdsq) {
                    bdsq = dsq;
                    bj = j;
                }
            }
            d1[i] = sqrt(bdsq);
            clusters[bj].push_back(i);
            total_cost += pts[i].w * d1[i];
        }

        if (total_cost < best_cost) {
            best_cost = total_cost;
            best_c = centers;
        }

        if (abs(prev_cost - total_cost) / max(1.0, total_cost) < 1e-6) break;
        prev_cost = total_cost;

        for (int j = 0; j < m; j++) {
            if (clusters[j].empty()) {
                int wi = 0;
                double mwd = -1.0;
                for (int i = 0; i < n; i++) {
                    if (pts[i].w * d1[i] > mwd) {
                        mwd = pts[i].w * d1[i];
                        wi = i;
                    }
                }
                centers[j] = {pts[wi].x, pts[wi].y};
                d1[wi] = 0;
            } else {
                centers[j] = weiszfeld_exact(clusters[j], centers[j], 1, weisz_iter);
            }
        }
    }

    centers = best_c;
    return best_cost;
}

vector<pair<double, double>> bisecting_init() {
    struct Node {
        vector<int> ids;
        pair<double, double> center;
        double cost;
        pair<double, double> c1, c2;
        vector<int> left_ids, right_ids;
        double split_gain;
        bool evaluated;
    };

    vector<Node> active;
    active.reserve(m);

    Node root;
    root.ids.resize(n);
    iota(root.ids.begin(), root.ids.end(), 0);
    root.center = weiszfeld_exact(root.ids, {0, 0}, 0, 30);
    root.cost = eval_cluster(root.ids, root.center.first, root.center.second);
    root.evaluated = false;
    active.push_back(move(root));

    auto evaluate_split = [&](Node& nd) {
        if (nd.evaluated) return;
        nd.evaluated = true;
        if (nd.ids.size() <= 1 || nd.cost <= 1e-9) {
            nd.split_gain = -1.0;
            return;
        }

        int far1 = nd.ids[0];
        double max_wd = -1.0;
        for (int idx : nd.ids) {
            double wd = pts[idx].w * dist(pts[idx].x, pts[idx].y, nd.center.first, nd.center.second);
            if (wd > max_wd) {
                max_wd = wd;
                far1 = idx;
            }
        }

        int far2 = nd.ids[0];
        double max_d2 = -1.0;
        for (int idx : nd.ids) {
            double wd = pts[idx].w * dist(pts[idx].x, pts[idx].y, pts[far1].x, pts[far1].y);
            if (wd > max_d2) {
                max_d2 = wd;
                far2 = idx;
            }
        }

        pair<double, double> p1 = {pts[far1].x, pts[far1].y};
        pair<double, double> p2 = {pts[far2].x, pts[far2].y};
        if (dist_sq(p1.first, p1.second, p2.first, p2.second) < 1e-12) {
            p2 = nd.center;
        }

        vector<int> L, R;
        for (int it = 0; it < 6; it++) {
            L.clear();
            R.clear();
            for (int idx : nd.ids) {
                double d_l = dist_sq(pts[idx].x, pts[idx].y, p1.first, p1.second);
                double d_r = dist_sq(pts[idx].x, pts[idx].y, p2.first, p2.second);
                if (d_l <= d_r) L.push_back(idx);
                else R.push_back(idx);
            }
            if (L.empty() || R.empty()) break;
            p1 = weiszfeld_exact(L, p1, 1, 10);
            p2 = weiszfeld_exact(R, p2, 1, 10);
        }

        if (L.empty() || R.empty()) {
            L.clear(); R.clear();
            for (size_t i = 0; i < nd.ids.size(); i++) {
                if (i < nd.ids.size() / 2) L.push_back(nd.ids[i]);
                else R.push_back(nd.ids[i]);
            }
            p1 = weiszfeld_exact(L, p1, 0, 10);
            p2 = weiszfeld_exact(R, p2, 0, 10);
        }

        double new_cost = eval_cluster(L, p1.first, p1.second) + eval_cluster(R, p2.first, p2.second);
        nd.c1 = p1;
        nd.c2 = p2;
        nd.left_ids = move(L);
        nd.right_ids = move(R);
        nd.split_gain = max(0.0, nd.cost - new_cost);
    };

    while ((int)active.size() < m) {
        int best_idx = -1;
        double best_gain = -1.0;
        for (int i = 0; i < (int)active.size(); i++) {
            evaluate_split(active[i]);
            if (active[i].split_gain > best_gain) {
                best_gain = active[i].split_gain;
                best_idx = i;
            }
        }
        if (best_idx == -1 || best_gain <= 0) break;

        Node L_node, R_node;
        L_node.ids = move(active[best_idx].left_ids);
        L_node.center = active[best_idx].c1;
        L_node.cost = eval_cluster(L_node.ids, L_node.center.first, L_node.center.second);
        L_node.evaluated = false;

        R_node.ids = move(active[best_idx].right_ids);
        R_node.center = active[best_idx].c2;
        R_node.cost = eval_cluster(R_node.ids, R_node.center.first, R_node.center.second);
        R_node.evaluated = false;

        active[best_idx] = move(L_node);
        active.push_back(move(R_node));
    }

    vector<pair<double, double>> res;
    for (auto& nd : active) res.push_back(nd.center);
    while ((int)res.size() < m) {
        res.push_back({pts[res.size() % n].x, pts[res.size() % n].y});
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto start_time = chrono::steady_clock::now();

    if (!(cin >> n >> m)) return 0;

    pts.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y >> pts[i].w;
    }

    cout << fixed << setprecision(7);

    vector<Point> unique_pts;
    {
        vector<Point> sp = pts;
        sort(sp.begin(), sp.end(), [](const Point& a, const Point& b) {
            if (abs(a.x - b.x) > 1e-9) return a.x < b.x;
            return a.y < b.y;
        });
        for (const auto& p : sp) {
            if (!unique_pts.empty() && dist_sq(unique_pts.back().x, unique_pts.back().y, p.x, p.y) < 1e-14) {
                unique_pts.back().w += p.w;
            } else {
                unique_pts.push_back(p);
            }
        }
    }
    pts = unique_pts;
    n = pts.size();

    if (m >= n) {
        for (int i = 0; i < m; i++) {
            int idx = min(i, n - 1);
            cout << pts[idx].x << " " << pts[idx].y << "\n";
        }
        return 0;
    }

    if (m == 1) {
        vector<int> all_idx(n);
        iota(all_idx.begin(), all_idx.end(), 0);
        auto ans = weiszfeld_exact(all_idx, {0, 0}, 0, 500);
        cout << ans.first << " " << ans.second << "\n";
        return 0;
    }

    vector<pair<double, double>> best_centers(m);
    double best_cost = 1e300;

    {
        auto c_bisect = bisecting_init();
        double cost = run_lloyd(c_bisect, 50, 25);
        if (cost < best_cost) {
            best_cost = cost;
            best_centers = c_bisect;
        }
    }

    vector<float> p_dist(n * n);
    for (int i = 0; i < n; i++) {
        p_dist[i * n + i] = 0.0f;
        for (int j = i + 1; j < n; j++) {
            float d = (float)dist(pts[i].x, pts[i].y, pts[j].x, pts[j].y);
            p_dist[i * n + j] = d;
            p_dist[j * n + i] = d;
        }
    }

    {
        vector<pair<double, double>> c_greedy(m);
        vector<double> cur_d(n, 1e300);

        for (int step = 0; step < m; step++) {
            int best_cand = 0;
            if (step == 0) {
                double best_init_c = 1e300;
                for (int cand = 0; cand < n; cand++) {
                    double c = 0;
                    const float* row = &p_dist[cand * n];
                    for (int i = 0; i < n; i++) c += pts[i].w * row[i];
                    if (c < best_init_c) {
                        best_init_c = c;
                        best_cand = cand;
                    }
                }
            } else {
                double max_gain = -1.0;
                int stride = (n * m > 400000) ? max(1, n / 250) : 1;
                vector<int> ord(n);
                iota(ord.begin(), ord.end(), 0);
                if (stride > 1) {
                    sort(ord.begin(), ord.end(), [&](int a, int b) {
                        return pts[a].w * cur_d[a] > pts[b].w * cur_d[b];
                    });
                }
                int limit = (stride > 1) ? min(n, 300) : n;
                for (int k = 0; k < limit; k++) {
                    int cand = ord[k];
                    double gain = 0;
                    const float* row = &p_dist[cand * n];
                    for (int i = 0; i < n; i++) {
                        if (row[i] < cur_d[i]) {
                            gain += pts[i].w * (cur_d[i] - row[i]);
                        }
                    }
                    if (gain > max_gain) {
                        max_gain = gain;
                        best_cand = cand;
                    }
                }
            }

            c_greedy[step] = {pts[best_cand].x, pts[best_cand].y};
            const float* row = &p_dist[best_cand * n];
            for (int i = 0; i < n; i++) {
                if (row[i] < cur_d[i]) cur_d[i] = row[i];
            }
        }

        double cost = run_lloyd(c_greedy, 50, 25);
        if (cost < best_cost) {
            best_cost = cost;
            best_centers = c_greedy;
        }
    }

    mt19937_64 rng(20261013);
    uniform_real_distribution<double> uni(0.0, 1.0);
    vector<double> d1(n), d2(n);
    vector<int> c1(n);

    auto do_pam_local_search = [&](vector<pair<double, double>>& centers, double& cur_best_cost, double time_limit) {
        while (true) {
            auto now = chrono::steady_clock::now();
            if (chrono::duration<double>(now - start_time).count() > time_limit) break;

            vector<double> removal_loss(m, 0.0);
            for (int i = 0; i < n; i++) {
                double b1 = 1e300, b2 = 1e300;
                int id1 = 0;
                for (int j = 0; j < m; j++) {
                    double d = dist(pts[i].x, pts[i].y, centers[j].first, centers[j].second);
                    if (d < b1) {
                        b2 = b1;
                        b1 = d;
                        id1 = j;
                    } else if (d < b2) {
                        b2 = d;
                    }
                }
                d1[i] = b1;
                d2[i] = b2;
                c1[i] = id1;
                removal_loss[id1] += pts[i].w * (b2 - b1);
            }

            int rem_j = min_element(removal_loss.begin(), removal_loss.end()) - removal_loss.begin();
            double loss = removal_loss[rem_j];

            int best_cand = -1;
            double max_gain = loss;

            vector<int> cand_ord(n);
            iota(cand_ord.begin(), cand_ord.end(), 0);
            sort(cand_ord.begin(), cand_ord.end(), [&](int a, int b) {
                return pts[a].w * d1[a] > pts[b].w * d1[b];
            });

            int check_limit = min(n, 400);
            for (int k = 0; k < check_limit; k++) {
                int cand = cand_ord[k];
                double gain = 0;
                const float* row = &p_dist[cand * n];
                for (int i = 0; i < n; i++) {
                    double eff_d = (c1[i] == rem_j) ? d2[i] : d1[i];
                    if (row[i] < eff_d) {
                        gain += pts[i].w * (eff_d - row[i]);
                    }
                }
                if (gain > max_gain) {
                    max_gain = gain;
                    best_cand = cand;
                }
            }

            if (best_cand != -1 && (max_gain - loss) > 1e-5 * cur_best_cost) {
                auto next_centers = centers;
                next_centers[rem_j] = {pts[best_cand].x, pts[best_cand].y};
                double nc = run_lloyd(next_centers, 25, 20);
                if (nc < cur_best_cost - 1e-7) {
                    cur_best_cost = nc;
                    centers = next_centers;
                    continue;
                }
            }
            break;
        }
    };

    do_pam_local_search(best_centers, best_cost, 1.50);

    int run = 0;
    while (true) {
        auto now = chrono::steady_clock::now();
        double elapsed = chrono::duration<double>(now - start_time).count();
        if (elapsed > 2.22) break;
        run++;

        vector<pair<double, double>> centers;
        if (run % 2 == 1) {
            centers = best_centers;
            int k_perturb = max(1, min(m / 3, 5));
            for (int p = 0; p < k_perturb; p++) {
                vector<double> rem_loss(m, 0.0);
                for (int i = 0; i < n; i++) {
                    double b1 = 1e300, b2 = 1e300;
                    int id1 = 0;
                    for (int j = 0; j < m; j++) {
                        double d = dist(pts[i].x, pts[i].y, centers[j].first, centers[j].second);
                        if (d < b1) { b2 = b1; b1 = d; id1 = j; }
                        else if (d < b2) { b2 = d; }
                    }
                    d1[i] = b1;
                    rem_loss[id1] += pts[i].w * (b2 - b1);
                }
                int rj = min_element(rem_loss.begin(), rem_loss.end()) - rem_loss.begin();
                double sum_wd = 0;
                for (int i = 0; i < n; i++) sum_wd += pts[i].w * d1[i];
                if (sum_wd > 1e-12) {
                    double pick = uni(rng) * sum_wd;
                    int chosen = n - 1;
                    for (int i = 0; i < n; i++) {
                        pick -= pts[i].w * d1[i];
                        if (pick <= 0) { chosen = i; break; }
                    }
                    centers[rj] = {pts[chosen].x, pts[chosen].y};
                }
            }
        } else {
            centers.resize(m);
            double total_w = 0;
            for (int i = 0; i < n; i++) total_w += pts[i].w;
            double r = uni(rng) * total_w;
            int first_idx = 0;
            for (int i = 0; i < n; i++) {
                r -= pts[i].w;
                if (r <= 0) { first_idx = i; break; }
            }
            centers[0] = {pts[first_idx].x, pts[first_idx].y};
            for (int i = 0; i < n; i++) {
                d1[i] = dist(pts[i].x, pts[i].y, centers[0].first, centers[0].second);
            }
            for (int j = 1; j < m; j++) {
                double sum_wd = 0;
                for (int i = 0; i < n; i++) sum_wd += pts[i].w * d1[i];
                int chosen = rng() % n;
                if (sum_wd > 1e-12) {
                    double pick = uni(rng) * sum_wd;
                    for (int i = 0; i < n; i++) {
                        pick -= pts[i].w * d1[i];
                        if (pick <= 0) { chosen = i; break; }
                    }
                }
                centers[j] = {pts[chosen].x, pts[chosen].y};
                for (int i = 0; i < n; i++) {
                    d1[i] = min(d1[i], dist(pts[i].x, pts[i].y, centers[j].first, centers[j].second));
                }
            }
        }

        double cost = run_lloyd(centers, 25, 15);
        if (cost < best_cost) {
            best_cost = cost;
            best_centers = centers;
            do_pam_local_search(best_centers, best_cost, 2.25);
        }
    }

    run_lloyd(best_centers, 25, 80);

    for (int j = 0; j < m; j++) {
        cout << best_centers[j].first << " " << best_centers[j].second << "\n";
    }

    return 0;
}
