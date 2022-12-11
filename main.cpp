#include <iostream>
#include <vector>
#include <map>

using namespace std;

int vowelSubstring(const string& s) {
    function<bool(char)> isVowel;
    isVowel = [&] (char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    cerr << s << endl;
    int answer = 0;
    string vowels = "aeiou";
    map<char, vector<int>> indices;
    int l = INT_MAX, r = INT_MIN;
    for (int i = 0; i < s.size(); ++i) {
        if (isVowel(s[i])) {
            indices[s[i]].push_back(i);
            l = min(l, i);
            r = max(r, i);
            int mini = INT_MAX;
            bool allHere = true;
            for (auto j : vowels) {
                if (indices[j].empty()) {
                    allHere = false;
                    break;
                }
                mini = min(mini, indices[j].back());
            }
            if (!allHere) {
                continue;
            }
            answer += (mini - l + 1);
        } else {
            l = INT_MAX, r = INT_MIN;
            indices.clear();
        }
    }
    return answer;
}

int largestSubgrid(vector<vector<int>> grid, int maxSum) {
    int n = (int)grid.size();
    vector<vector<int>> pref(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        vector<int> row(n);
        for (int j = 0; j < n; ++j) {
            row[j] = grid[i][j];
            if (j > 0) {
                row[j] += row[j - 1];
            }
            pref[i][j] = row[j];
            if (i > 0) {
                pref[i][j] += pref[i - 1][j];
            }
        }
    }

    function<int(int, int, int)> getSum;
    getSum = [&] (int x1, int y1, int len) {
        int x2 = x1 + len - 1, y2 = y1 + len - 1;
        int sum = pref[x2][y2];
        if (x1 > 0) {
            sum -= pref[x1 - 1][y2];
        }
        if (y1 > 0) {
            sum -= pref[x2][y1 - 1];
        }
        if (x1 > 0 && y2 > 0) {
            sum += pref[x1 - 1][y2 - 1];
        }
        return sum;
    };

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int l = 0, r = min(n - i, n - j) + 1;
            while (r - l > 1) {
                int mid = (r + l) >> 1;
                if (getSum(i, j, mid) > maxSum) {
                    r = mid - 1;
                } else {
                    l = mid;
                }
            }
            answer = max(answer, l);
        }
    }

    return answer;
}

int main() {
    cout << "vowelSubstring Tests" << endl;
    cout << vowelSubstring("aaeiouaxu") << endl;
    cout << vowelSubstring("aaaaaaeiou") << endl;
    cout << "largestSubgrid Tests" << endl;
    cout << largestSubgrid({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, 4) << endl;
    cout << largestSubgrid({{1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}, {4, 4, 4, 4}}, 39) << endl;
    return 0;
}
