#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<double, int> pdi;

vector<int> solution(int N, vector<int> stages) {
    int n = stages.size();
    vector<int> arr(N + 2, 0);
    vector<pdi> ret;
    for (int i : stages) arr[i] += 1;
    for (int i = 1;i <= N;++i) {
        if (n == 0) ret.emplace_back(pdi(0, i));    // 0 처리 해줘야함
        else ret.emplace_back(pdi((double)arr[i] / n, i));
        n -= arr[i];
    }
    sort(ret.begin(), ret.end(), [&](const pdi a, const pdi b) {
        return a.first != b.first ? a.first > b.first:a.second < b.second;
        });
    vector<int> answer;
    for (int i = 0;i < N;++i) answer.emplace_back(ret[i].second);
    return answer;
}