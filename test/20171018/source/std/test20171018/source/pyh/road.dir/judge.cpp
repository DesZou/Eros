#include <bits/stdc++.h>

typedef long long LL;

#define FOR(i, a, b) for (int i = (a), i##_END_ = (b); i <= i##_END_; i++)
#define DNF(i, a, b) for (int i = (a), i##_END_ = (b); i >= i##_END_; i--)

template <typename Tp> void in(Tp &x) {
	char ch = getchar(), f = 1; x = 0;
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if (ch == '-') f = -1, ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= f;
}

template <typename Tp> Tp Max(const Tp &x, const Tp &y) {return x > y ? x : y;}
template <typename Tp> Tp Min(const Tp &x, const Tp &y) {return x < y ? x : y;}
template <typename Tp> bool chkmax(Tp &x, Tp y) {return x >= y ? 0 : (x=y, 1);}
template <typename Tp> bool chkmin(Tp &x, Tp y) {return x <= y ? 0 : (x=y, 1);}

char command[100];

int main()
{
	system("g++ road.cpp -o road -O2");
	system("g++ force.cpp -o force -O2");
	system("g++ make.cpp -o make -O2");

	int tot = 0;
	
	while (true) {
		++tot;
		sprintf(command, "echo %d | ./make", tot);
		system(command);
		system("./force");
		system("./road");
		if (!system("diff road.out road.ans")) {
			printf("AC %d\n", tot);
		}
		else {
			printf("WA %d\n", tot);
			break;
		}
	}
	
	return 0;
}
