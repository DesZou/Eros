#include <set>
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
typedef std :: pair<int, int> ii;

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

int n, m, x, y, z, k, num;

namespace P1{

	const int maxx = 300 + 25;
	const int Inf = 1061109567;
	const int mod = 1e9 + 7;
	
	int dis[maxx][maxx], f[maxx][maxx];

	LL ans = 0;
	
	int main(){
		memset(dis, 0x3f, sizeof(dis));
		memset(f, 0, sizeof(f));
		Rep(i, 1, n){
			scanf("%d%d", &x, &y);
			dis[i][x] = y;
		}
		Rep(k, 1, n){
			Rep(i, 1, n){
				if(k != i){
					Rep(j, 1, n){
						if(i != j)
							dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
					}
				}
			}
		}
		Rep(i, 1, n){
			Rep(j, 1, n){
				if(i == j) f[i][j] = 0;
				else if(dis[i][j] == Inf){
					f[i][j] = -1;
				}
				else f[i][j] = dis[i][j];
			}
		}
		
		Rep(i, 1, n){
			Rep(j, 1, n){
				ans = (ans + f[i][j] + mod) % mod;
			}
		}
		printf("%lld\n", ans);
	}
	
}

const int maxx = 500000 + 25;
const int mod = 1e9 + 7;

int ftr[maxx], cnt[maxx], a[maxx];
LL  sum[maxx], size[maxx];

LL cur, ans;

int find(int x){
	return ftr[x] == x? x : ftr[x] = find(ftr[x]);
}

LL calc(int x){
	return (LL)(1ll * x * (x + 1) * 500000004) % mod;
}

int main(){
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	scanf("%d", &n);
	if(n <= 300) P1 :: main();
	else{
		Rep(i, 1, n)
			ftr[i] = i;
		Rep(i, 1, n){
			scanf("%d%d", &x, &a[i]);
			if(find(i) != find(x))
				ftr[find(i)] = find(x);
		}
		Rep(i, 1, n){
			int tmp = find(i);
			size[tmp] ++;
			sum[tmp] = (sum[tmp] + a[i]) % mod;
		}
		Rep(i, 1, n){
			if(size[i]){
				ans = (ans + (calc(size[i]) * sum[i]) % mod) % mod;
				ans = (ans + (size[i] * (n - size[i]) * (-1)) + mod) % mod;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
