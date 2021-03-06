class Solution {
private:
    int findkth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
        if (i == nums1.size()) {
            return nums2[j + k - 1];
        }
        if (j == nums2.size()) {
            return nums1[i + k - 1];
        }
        if (k == 1) {
            return min(nums1[i], nums2[j]);
        }
        int contrib1 = i + k / 2 - 1;
        if (contrib1 >= nums1.size()) {
            contrib1 = nums1.size() - 1;
        }
        int contrib2 = j + k / 2 - 1;
        if (contrib2 >= nums2.size()) {
            contrib2 = nums2.size() - 1;
        }
        if (nums1[contrib1] <= nums2[contrib2]) {
            return findkth(nums1, contrib1 + 1, nums2, j, k - (contrib1 - i + 1));
        }
        return findkth(nums1, i, nums2, contrib2 + 1, k - (contrib2 - j + 1));
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int cnt = nums1.size() + nums2.size();
        if (cnt % 2 == 1) {
            return findkth(nums1, 0, nums2, 0, cnt / 2 + 1);
        }
        return (findkth(nums1, 0, nums2, 0, cnt / 2) + findkth(nums1, 0, nums2, 0, cnt / 2 + 1)) / 2.0;
    }
};

// Perfect case would be each vector contributes half into the final answer
// But maybe one array could contribute more than others
// So when doing bin search, we could only get rid of the half, with smaller mid value, at one time
// and then update nth and find a new nth result

// Also, we need to consider odd even.
class Solution {
private:
    int find(vector<int>& nums1, int start1, vector<int>& nums2, int start2, int nth) {
        // stopping cases
        // nth = 1 (no contrib if /2) or no contribution from one of the vectors
        if (start1 >= nums1.size()) {
            return nums2[start2 + nth - 1];
        }
        if (start2 >= nums2.size()) {
            return nums1[start1 + nth - 1];
        }
        if (nth == 1) {
            return min(nums1[start1], nums2[start2]);
        }
        
        // the amount at most a vector could contribute
        int contrib1 = min((int)nums1.size() - start1, nth / 2);
        int contrib2 = min((int)nums2.size() - start2, nth / 2);
        if (nums1[start1 + contrib1 - 1] <= nums2[start2 + contrib2 - 1]) {
            start1 += contrib1;
            nth -= contrib1;
        } else {
            start2 += contrib2;
            nth -= contrib2;
        }
        return find(nums1, start1, nums2, start2, nth);
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total = nums1.size() + nums2.size();
        if (total % 2 == 0) {
            return (find(nums1, 0, nums2, 0, total / 2) + find(nums1, 0, nums2, 0, total / 2 + 1)) / 2.0;
        }
        return find(nums1, 0, nums2, 0, total / 2 + 1);
        
    }
};

// The above one is even cleaner. Instead of getting rid of els in nums2 when els in nums1 are not enough, we use a min to get rid of the one we want.
// Other solutions ============================================================
// Much cleaner. 90% 100%
class Solution {
private:
    int _find(vector<int>& nums1, vector<int>& nums2, int start1, int start2, int k) {
        while(true) {
            // When? [[2],[1,3,4,5,6]]
            if (start1 >= nums1.size()) {
                // suppose k == 1, just look for the starter element
                return nums2[start2 + k - 1];
            }
            if (start2 >= nums2.size()) {
                return nums1[start1 + k - 1];
            }
            if (k == 1) {
                return min(nums1[start1], nums2[start2]);
            }
            // Careful here. When k is odd, we first get rid of floor(k/2) elements
            // eg. When k = 3, each should contribute only 1 (starter) element.
            int guess1 = start1 + k/2 - 1;
            int guess2 = start2 + k/2 - 1;
            if (guess2 >= nums2.size() || (guess1 < nums1.size() && nums1[guess1] < nums2[guess2])) {
                // skip k/2 element, when k = 3, skip only the starter
                start1 += k/2;
            } else {
                start2 += k/2;
            }
            k -= k/2;
        }
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int s1 = nums1.size();
        int s2 = nums2.size();
        int s = s1 + s2;
        if (s % 2 == 1) {
            return _find(nums1, nums2, 0, 0, s/2 + 1);
        } else {
            return (_find(nums1, nums2, 0, 0, s/2) + _find(nums1, nums2, 0, 0, s/2 + 1)) / 2.0;
        }
    }
};

// 40% 40%, too complicated
class Solution {
private:
    vector<int> _findkth(vector<int>& nums1, vector<int>& nums2, int start1, int start2, int kth) {
        //Much simpler if kth start with 1!
        if (start1 >= nums1.size()) {
            return vector<int> {-1, start2 + kth};
        }
        if (start2 >= nums2.size()) {
            return vector<int> {start1 + kth, -1};
        }
        if (kth == 0) {
            return vector<int> {start1, start2};
        }
        int guess1 = start1 + kth / 2;
        int guess2 = start2 + kth / 2;
        //Careful! Boundry case
        if (guess2 >= nums2.size() || (guess1 < nums1.size() && nums1[guess1] < nums2[guess2])) {
            //Careful! At least get rid of one result
            //Cant use guess1+1 for all. May skip the correct answer ([1], [2,3,4,5])
            if (kth / 2 == 0) {
                return _findkth(nums1, nums2, guess1 + 1, start2, kth - 1);
            } else {
                return _findkth(nums1, nums2, guess1, start2, kth - kth / 2);
            }
        } else {
            if (kth / 2 == 0) {
                return _findkth(nums1, nums2, start1, guess2 + 1, kth - 1);
            } else {
                return _findkth(nums1, nums2, start1, guess2, kth - kth / 2);
            }
        }
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int s1 = nums1.size();
        int s2 = nums2.size();
        int s = s1 + s2;
        vector<int> target_indexes;
        if (s % 2 == 1) {
            target_indexes = _findkth(nums1, nums2, 0, 0, s / 2);
            if (target_indexes[0] == -1) {
                return nums2[target_indexes[1]];
            } else if (target_indexes[1] == -1) {
                return nums1[target_indexes[0]];
            } else {
                return min(nums1[target_indexes[0]], nums2[target_indexes[1]]);
            }
        } else {
            target_indexes = _findkth(nums1, nums2, 0, 0, s / 2 - 1);
            if (target_indexes[0] == -1) {
                // To get a double arithmetic result. At least one of the ints must be explicitly casted to a double.
                return (nums2[target_indexes[1]] + nums2[target_indexes[1] + 1]) / 2.0;
            } else if (target_indexes[1] == -1) {
                return (nums1[target_indexes[0]] + nums1[target_indexes[0] + 1]) / 2.0;
            } else if (nums1[target_indexes[0]] == min(nums1[target_indexes[0]], nums2[target_indexes[1]])){
                if (target_indexes[0] + 1 >= nums1.size()) {
                    return (nums1[target_indexes[0]] + nums2[target_indexes[1]]) / 2.0;
                } else {
                    return (nums1[target_indexes[0]] + min(nums1[target_indexes[0] + 1], nums2[target_indexes[1]])) / 2.0;
                }
            } else {
                if (target_indexes[1] + 1 >= nums2.size()) {
                    return (nums2[target_indexes[1]] + nums1[target_indexes[0]]) / 2.0;
                } else {
                    return (nums2[target_indexes[1]] + min(nums1[target_indexes[0]], nums2[target_indexes[1] + 1])) / 2.0;
                }
                
            }
        }
    }
};


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        if (len1 > len2) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int i_start = 0;
        int i_end = len1;
        //double:
        //https://stackoverflow.com/questions/7571326/why-does-dividing-two-int-not-yield-the-right-value-when-assigned-to-double
        double min_right;
        double max_left;

        while (i_start <= i_end) {
            //binary search
            int i = (i_start + i_end) / 2;
            int j = (len1 + len2) / 2 - i;
            if (i > 0 && nums1[i - 1] > nums2[j]) {
                i_end = i - 1;
            } else if (i < len1 && nums2[j - 1] > nums1[i]) {
                i_start = i + 1;
            } else {
                //perfect i and j
                //brutal enumeration method to get final result:
                if((len1 + len2) % 2 == 1) {
                    //include condition: len1 == 0
                    if (i == len1) {
                        return nums2[j];
                    } else {
                        return min(nums1[i], nums2[j]);
                    }
                } else {
                     if (len1 == 0) {
                        min_right = nums2[j];
                        max_left = nums2[j - 1];
                    } else if (i == 0) {
                        if (j == len2) {
                            min_right = nums1[i];
                        } else {
                            min_right = min(nums1[i], nums2[j]);
                        }

                        max_left = nums2[j - 1];
                    } else if (i == len1) {
                        if (j == 0) {
                            max_left = nums1[i - 1];
                        } else {
                            max_left = max(nums1[i - 1], nums2[j - 1]);
                        }
                        min_right = nums2[j];
                    } else {
                        min_right = min(nums1[i], nums2[j]);
                        max_left = max(nums1[i - 1], nums2[j - 1]);
                    }
                    return (min_right + max_left) / 2;
                }
            }
        }
    }
};
