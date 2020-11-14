#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

int solution(string str1, string str2) {
    int answer = 0;
    unordered_map<string, int> s1, s2;
    for (int i = 0;i < str1.length() - 1;++i) {
        if (str1[i] >= 'A' && str1[i] <= 'Z') str1[i] = str1[i] - 'A' + 'a';
        if (str1[i + 1] >= 'A' && str1[i + 1] <= 'Z') str1[i + 1] = str1[i + 1] - 'A' + 'a';
        if (str1[i] < 'a' || str1[i]>'z' || str1[i + 1] < 'a' || str1[i + 1]>'z') continue;
        string x = ""; x += str1[i]; x += str1[i + 1];
        ++s1[x];
    }
    for (int i = 0;i < str2.length() - 1;++i) {
        if (str2[i] >= 'A' && str2[i] <= 'Z') str2[i] = str2[i] - 'A' + 'a';
        if (str2[i + 1] >= 'A' && str2[i + 1] <= 'Z') str2[i + 1] = str2[i + 1] - 'A' + 'a';
        if (str2[i] < 'a' || str2[i]>'z' || str2[i + 1] < 'a' || str2[i + 1]>'z') continue;
        string x = ""; x += str2[i]; x += str2[i + 1];
        ++s2[x];
    }
    if (s1.empty() && s2.empty()) return 65536;
    int mn = 0, mx = 0;
    for (auto e : s1) {
        if (s2.find(e.first) == s2.end()) {
            mx += e.second;
            continue;
        }
        mn += min(e.second, s2[e.first]);
        mx += max(e.second, s2[e.first]);
    }
    for (auto e : s2) {
        if (s1.find(e.first) == s1.end()) mx += e.second;      
    }
    answer = 65536.0f * (double)mn / mx;
    return answer;
}