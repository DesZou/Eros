#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>

#define Rep(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i<=(i##_END);++i)
#define For(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i!=(i##_END);++i)
#define Lop(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i>=(i##_END);--i)
#define Dnt(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i!=(i##_END);--i)

#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#define Newline (putchar(10))

using std :: max;
using std :: min;

typedef long long LL;

template <class T> bool chkmax(T &x, const T &y){
	return y > x? x = y, true : false;
}
template <class T> bool chkmin(T &x, const T &y){
	return y < x? x = y, true : false;
}

namespace FI{

	const int L = 1 << 15 | 1;
	char buffer[L], *S, *T;

	inline char Getchar(){
		if(S == T) T = (S = buffer) + fread(buffer, 1, L, stdin);
		return S == T? EOF : *S ++;
	}

	template <class T> void read(T &in){
		char ch; int f = 1;
		for(ch = Getchar(); !isdigit(ch); ch = Getchar()) if(ch == '-') f = -1;
		for(in = 0; isdigit(ch); ch = Getchar()) in = in * 10 + ch - '0';
		in *= f;
	}
	
}

const int maxx = 100000 + 25;

int n, m, x, y, z, k, num;

LL  mod, tmp, cur, ans;

LL  a[maxx];

int main(){
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	scanf("%d%lld", &n, &mod);
	Rep(i, 1, n)
		scanf("%lld", &a[i]);
	Rep(i, 1, n){
		tmp = ((a[i] * cur) % mod + a[i]) % mod;
		ans = (ans + tmp) % mod;
		cur = tmp;
	}
	printf("%lld\n", ans);
	return 0;
}
