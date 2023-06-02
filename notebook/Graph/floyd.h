// Tested:
// - https://cses.fi/problemset/task/1672/
// - (trace) https://oj.vnoi.info/problem/floyd

struct Floyd {

    Floyd(int _n, const vector<vector<ll>> _c) : n(_n), c(_c), trace(n+1) {
        for (int i = 1; i <= n; i++) {
            trace[i] = vector<int> (n+1, -1);
            for (int j = 1; j <= n; j++) {
                if (c[i][j] == INF) trace[i][j] = -1;
                else trace[i][j] = i;
            }
        }

        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (c[i][k] != INF && c[k][j] != INF && c[i][j] > c[i][k] + c[k][j]) {
                        c[i][j] = c[i][k] + c[k][j];
                        trace[i][j] = trace[k][j];
                    }
                }
            }
        }
    }

    // Return {distance, path}
    // If no path -> returns {-1, {}}
    pair<ll,vector<int>> get_path(int start, int target) {
        if (trace[start][target] == -1) return {-1, {}};

        vector<int> path;
        for (int u = target; u != start; u = trace[start][u]) {
            path.push_back(u);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return {c[start][target], path};
    }
    
    ll min_path(int start, int target){
        return c[start][target];
    }

    int n;
    vector<vector<ll>> c;
    vector<vector<int>> trace;
};