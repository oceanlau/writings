class Solution {
public:
    int hammingWeight(uint32_t n) {
        uint32_t mask = 1;
        int sum = 0;
        int shift_cnt = 32;
        while (shift_cnt > 0) {
            if (mask & n) {
                sum ++;
            }
            mask <<= 1;
            shift_cnt --;
        }
        return sum;
    }
};
