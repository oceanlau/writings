class Solution {
public:
    bool isReflected(vector<vector<int>>& points) {
        int min_x = INT_MAX;
        int max_x = INT_MIN;
        unordered_set<string> x_ys;
        for (int i = 0; i < points.size(); i ++) {
            min_x = min(min_x, points[i][0]);
            max_x = max(max_x, points[i][0]);
            x_ys.insert(to_string(points[i][0]) + '_' + to_string(points[i][1]));
        }
        double mid = min_x + (max_x - min_x) / 2.0;
        for (int i = 0; i < points.size(); i ++) {
            int x = mid + (mid - points[i][0]);
            string new_x_y = to_string(x) + '_' + to_string(points[i][1]);
            if (!x_ys.count(new_x_y)) {
                return false;
            }
        }
        return true;
    }
};

//95% 100%
class Solution {
public:
    bool isReflected(vector<vector<int>>& points) {
        unordered_map<int, set<int>> y_to_xs;
        for (const vector<int>& point : points) {
            y_to_xs[point[1]].insert(point[0]);
        }
        double mid = 0;
        for (auto m_iter = y_to_xs.begin(); m_iter != y_to_xs.end(); m_iter++) {
            if (m_iter == y_to_xs.begin()) {
                //careful
                mid = (*(m_iter->second.begin()) + *prev(m_iter->second.end(), 1))/2.0;
            }
            //Cant compare bidirectional iteratorif inc and dec together! Missed!
            //for (; b != e; b++, e--) {
            //Dont inc dec b e at the same time
            for (auto b = m_iter->second.begin(), e = m_iter->second.end(); b != e; b++) {
                if (mid - *b != *(--e) - mid) {
                    return false;
                }
                // for odd num of elements
                if (b == e) {
                    break;
                }
            }
        }
        return true;
    }
};
