class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1) {
            return 1;
        }
        vector<int> ways(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                ways[j] += ways[j - 1];
            }
        }
        return ways.back();
    }
};

class Solution {
private:
    //grid m x n, starting from 0,0 (grid size 1x1)
    vector<vector<int>> _dp;
    int _getDp(int m, int n) {
        if (m < 0 || n < 0) {
            return 0;
        } else if (m == 0 || n == 0) {
            return 1;
        } else if (_dp[m][n] != 0) {
            return _dp[m][n];
        }
        _dp[m][n] = _getDp(m - 1, n) + _getDp(m, n - 1);
        return _dp[m][n];
    }
public:
    int uniquePaths(int m, int n) {
        _dp.resize(m, vector<int>(n, 0));
        return _getDp(m - 1, n - 1);
    }
};
