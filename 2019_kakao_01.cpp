#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<string> solution(vector<string> record) {
    int n = record.size();
    vector<vector<string>> log(n, vector<string>(3));
    unordered_map<string, string> user;
    for (int i = 0;i < n;++i) {
        string t = "";
        int idx = 0;
        for (int j = 0;j < record[i].length();++j) {
            if (record[i][j] == ' ') {
                log[i][idx++] = t;
                t = "";
                continue;
            }
            t += record[i][j];
        }
        log[i][idx] = t;
        if (log[i][0] == "Enter" || log[i][0] == "Change") {
            user[log[i][1]] = log[i][2];
        }
    }
    vector<string> answer;
    for (int i = 0;i < n;++i) {
        if (log[i][0] == "Enter") answer.emplace_back(user[log[i][1]] + "님이 들어왔습니다.");
        else if (log[i][0] == "Leave") answer.emplace_back(user[log[i][1]] + "님이 나갔습니다.");
    }
    return answer;
}