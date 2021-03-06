class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char, int> counter;
        char most_freq_char = ' ';
        int most_freq = 0;
        for (const char c : S) {
            if (++counter[c] > most_freq) {
                most_freq = counter[c];
                most_freq_char = c;
            }
        }
        if (most_freq > (S.length() + 1) / 2) {
            return "";
        }
        int i = 0;
        while (counter[most_freq_char] > 0) {
            S[i] = most_freq_char;
            i += 2;
            counter[most_freq_char] --;
        }
        for (auto& p : counter) {
            while (p.second > 0) {
                if (i >= S.length()) {
                    i = 1;
                }
                S[i] = p.first;
                i += 2;
                p.second --;
            }
        }
        return S;
    }
};

class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char, int> freq;
        int len = S.length();
        for(const char s : S) {
            freq[s]++;
        }
        priority_queue<pair<int, char>> pq;
        for (const auto& p : freq) {
            if(p.second > (len+1)/2) {
                return "";
            }
            pq.push(make_pair(p.second, p.first));
        }
        string res;
        while(pq.size() != 0){
            pair<int, char> p1 = pq.top();
            pq.pop();
            res += p1.second;
            if(pq.size() != 0) {
                pair<int, char> p2 = pq.top();
                pq.pop();
                res += p2.second;
                if (--p2.first > 0) {
                    pq.push(p2);
                }
            }
            if (--p1.first > 0) {
                pq.push(p1);
            }
            
        }
        return res;
    }
};

class Solution {
public:
    string reorganizeString(string S) {
        // put one of the most frequent char at odd poss
        // see is there enough how many spaces left for others
        int total = S.length();
        char most_frequent;
        int most_frequent_num = 0;
        vector<int> letters_cnt(256, 0);
        for (int i = 0; i < S.length(); i++) {
            if (++letters_cnt[S[i]] > most_frequent_num) {
                most_frequent = S[i];
                most_frequent_num = letters_cnt[S[i]];
            }
        }
        //suppose the most frequent one filled the odd poss
        if (total < 2*(most_frequent_num - 1)+1) {
            return "";
        }
        int i = 0;
        // one of the most frequent must be put at pos 0 (odd) to be safe
        // do an odd and an even sweep
        while (letters_cnt[most_frequent] > 0) {
            S[i] = most_frequent;
            letters_cnt[most_frequent] --;
            i += 2;
        }
        for (int j = 0; j < 256; j++) {
            if (letters_cnt[j] == 0) {
                continue;
            }
            while (letters_cnt[j] > 0) {
                //even sweep
                if (i >= S.length()) {
                    i = 1;
                }
                S[i] = (char)j;
                letters_cnt[j] --;
                i += 2;
            }
        }
        return S;
    }
};

// A bit tricky
class Solution {
public:
    string reorganizeString(string S) {
        int max_rooms = S.length();
        unordered_map<char, int> counter;
        int max_c = 0;
        char max_letter;
        for (const char c : S) {
            counter[c]++;
            if (counter[c] > max_c) {
                max_c = counter[c];
                max_letter = c;
            }            
        }
        if (2 * max_c > max_rooms + 1) {
            return "";
        }
        int idx = 0;
        // For bad case like aab -> baa
        while (counter[max_letter] != 0) {
            S[idx] = max_letter;
            idx +=2 ;
            counter[max_letter]--; 
        }
        // After max letter the rest just put in order
        for (auto iter = counter.begin(); iter != counter.end(); iter++) {
            while (iter->second != 0) {
                if (idx >= max_rooms) {
                    idx = 1;
                }
                S[idx] = iter->first;
                idx +=2 ;
                iter->second --;
            }
        }
        return S;
    }
};
