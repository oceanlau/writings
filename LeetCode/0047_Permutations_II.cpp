class Solution {
private:
    void _bt(vector<int>& nums, int start, vector<vector<int>>& res) {
        if (start == nums.size()) {
            res.push_back(nums);
            return;
        }
        unordered_set<int> used;
        for (int i = start; i < nums.size(); i++) {
            if (used.count(nums[i])) {
                continue;
            }
            used.insert(nums[i]);
            swap(nums[start], nums[i]);
            _bt(nums, start + 1, res);
            swap(nums[start], nums[i]);
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        _bt(nums, 0, res);
        return res;
    }
}; 

 class Solution {
 private:
     vector<int> _nums;
     void _bt(vector<vector<int>>& permutations, vector<int>& permutation, int begin, int end) {
         if (begin == end) {
             permutation.push_back(_nums[end]);
             permutations.push_back(permutation);
             permutation.pop_back();
             return;
         }
         vector<int> used;
         for (int i = begin; i <= end; i++) {
             if (find(used.begin(), used.end(), _nums[i]) != used.end()) {
                 continue;
             }
             used.push_back(_nums[i]);
             swap(_nums[begin], _nums[i]);
             permutation.push_back(_nums[begin]);
             _bt(permutations, permutation, begin + 1, end);
             permutation.pop_back();
             swap(_nums[begin], _nums[i]);
         }
     }
 public:
     vector<vector<int>> permuteUnique(vector<int>& nums) {
         _nums = nums;
         vector<vector<int>> permutations;
         vector<int> permutation;
         int end = nums.size() - 1;
         if (end < 0) {
             permutations.push_back(permutation);
             return permutations;
         }
         _bt(permutations, permutation, 0, end);
         return permutations;
     }
 };
