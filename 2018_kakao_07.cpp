// [1차] 다트 게임
#include <string>
#include <cmath>
using namespace std;

int solution(string dartResult) {
    int n = dartResult.length(), idx = 0, num[3] = { 0, };
    string tmp = "";
    for (int i = 0;i < n;++i) {
        if (dartResult[i] >= '0' && dartResult[i] <= '9') tmp += dartResult[i];      
        else if (dartResult[i] == 'S' || dartResult[i] == 'D' || dartResult[i] == 'T') {
            num[idx] = stoi(tmp);
            if (dartResult[i] == 'D') num[idx] = pow(num[idx], 2);
            else if (dartResult[i] == 'T') num[idx] = pow(num[idx], 3);
            ++idx;
            tmp = "";
        }
        else if (dartResult[i] == '*' || dartResult[i] == '#') {
            if (dartResult[i] == '*') {
                num[idx - 1] *= 2;
                if (idx - 1) num[idx - 2] *= 2;
            }
            else num[idx - 1] *= -1;        
        }
    }
    int answer = 0;
    for (int i = 0;i < 3;++i) answer += num[i];
    return answer;
}