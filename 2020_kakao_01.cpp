#include <iostream>
#include <string>
#include <vector>
using namespace std;

string str;

string solve(string p) {
	if (p == "") return "";
	string u = "", v = "";
	bool flag = 0;
	int cnt = 0, i = 0;

	for (;i < p.length();++i) {
		u += p[i];
		if (p[i] == '(') cnt++;
		else cnt--;

		if (cnt < 0) flag = 1;
		else if (cnt == 0) break;
	}

	if (i + 1 < p.length()) v = p.substr(i + 1);

	v = solve(v);

	if (flag) {
		string ret = "(" + v + ")";
		for (int i = 1;i < u.length() - 1;++i) {
			if (u[i] == '(') ret += ')';
			else ret += '(';
		}
		return ret;
	}
	else return u + v;
}

int main() {

	cin >> str;
	cout<< solve(str);

}