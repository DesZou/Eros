#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

using std :: max;
using std :: min;
using std :: set;
using std :: pair;
using std :: make_pair;
using std :: vector;
using std :: queue;
using std :: multiset;
using std :: priority_queue;

typedef long long LL;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const int maxm = 1e6 + 10;

template <class T> void read(T &in){
	in = 0; int f = 1 ;char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

LL A[maxm],sum[maxm],fac[maxm];
LL P,n,ans;

int main(){

	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	
	read(n); read(P); sum[0] = 1;	
	
	for(int i = 1;i <= n;i++) read(A[i]);
	for(int i = 1;i <= n;i++) sum[i] = (sum[i - 1] * A[i] % P + 1) % P;

	for(int i = 1;i <= n;i++){
		ans = (ans + A[i] * sum[i - 1] % P) % P;
	}

	printf("%lld\n",ans);
	
	return 0;
}
