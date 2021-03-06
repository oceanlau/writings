class Solution {
private:
    bool _is_concatenated(const string& word, const unordered_set<string>& dict) {
        if (word.length() == 0) {
            return false;
        }
        vector<bool> dp(word.length() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= word.length(); i ++) {
            for (int j = 0; j <= i; j ++) {
                if (!dp[j]) {
                    continue;
                }
                if (dict.count(word.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp.back();
    }
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        unordered_set<string> dict;
        for (const string& word : words) {
            dict.insert(word);
        }
        vector<string> result;
        for (const string& word : words) {
            dict.erase(word);
            if (_is_concatenated(word, dict)) {
                result.push_back(word);
            }
            dict.insert(word);
        }
        return result;
    }
};

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        unordered_set<string> dict(words.begin(), words.end());
        vector<string> res;
        for (const string& word : words) {
            vector<bool> dp(word.length() + 1, false);
            dp[0] = true;
            for (int i = 0; i <= word.length(); i++) {
                for (int j = i - 1; j >= 0; j--) {
                    string part = word.substr(j, i - j);
                    if (dp[j] && dict.count(part)) {
                        if (j == 0 && i == word.length()) {
                            continue;
                        }
                        dp[i] = true;
                        break;
                    }
                }
            }
            if (word.length() > 0 && dp[word.length()]) {
                res.push_back(word);
            }
        }
        return res;
    }
};
