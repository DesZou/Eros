#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

template <typename ty> void read(ty &x) {
	x = 0; int f = 1; char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x*10 + ch - '0'; ch = getchar(); }
	x *= f;
}
template <typename ty> ty Max(ty a, ty b) { return a > b ? a : b; }
template <typename ty> ty Min(ty a, ty b) { return a < b ? a : b; }

typedef long long LL;
typedef double db;
const int N = 1e5 + 5;

LL A[N], p, n, last, ans;

int main() {
	
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	
	read(n); read(p);
	for (int i = 1; i <= n; ++ i)
		read(A[i]);
	
	for (int i = n; i >= 1; -- i) {
		last = (last + 1) * A[i] % p;
		ans = (ans + last) % p;
	}
	
	printf("%lld\n", ans);
	
	return 0;
	
}
