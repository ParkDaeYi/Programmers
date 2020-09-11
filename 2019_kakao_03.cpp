#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

// 최소성 확인
bool chk(vector<int>& v, int cur) {
    for (int i : v) if ((i & cur) == i) return 0;
    return 1;
}

int solution(vector<vector<string>> relation) {
    int n = relation.size(), m = relation[0].size();
    vector<int> answer;
    for (int i = 1;i < (1 << m);++i) {
        // set 을 통해 유일성을 체크한다
        unordered_set<string> s;
        for (int j = 0;j < n;++j) {
            string str = "";
            for (int k = 0;k < m;++k) {
                // 각 속성은 왼쪽에서부터
                // 1, 10, 100, 1000 .... (2진수)
                if (i & (1 << k)) str += relation[j][k];
            }
            s.insert(str);
        }
        // 유일성을 만족했을 경우 최소성 조건에 부합하는지 확인
        if (s.size() == n && chk(answer, i)) answer.emplace_back(i);
    }
    return answer.size();
}