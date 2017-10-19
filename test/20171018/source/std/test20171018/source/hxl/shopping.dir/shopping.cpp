#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

using std :: max;
using std :: min;
using std :: set;
using std :: map;
using std :: pair;
using std :: make_pair;
using std :: vector;
using std :: queue;
using std :: multiset;
using std :: priority_queue;

typedef long long LL;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const int maxm = 1e5 + 10;

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

struct node{
	int x,y,id;
	bool operator < (const node &N) const {
		return y == N.y ? x > N.x : y < N.y;
	}
}A[maxm];

int rnk[maxm];
int cnt,n,m;

struct heap{
	priority_queue<int> que;
	map<int,int> mrk;
	
	heap(){mrk.clear();}
	
	int top(){
		while(mrk[que.top()] && !que.empty()) mrk[que.top()]--,que.pop();
		return que.top();
	}

	void pop(){
		que.pop();
	}

	void del(int x){
		mrk[x]++;
	}
	
	void push(int x){
		if(mrk[x]) mrk[x]--;
		else que.push(x);
	}
	
}que[maxm];

void build(int x,int l,int r){
	for(int i = l;i <= r;i++) que[x].push(A[i].x);
	if(l == r) return ;
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
}

int Query(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return que[x].top();
	int mid = (l + r) >> 1,res = 0;
	if(L <= mid) res = max(res,Query(x << 1,l,mid,L,R));
	if(R > mid) res = max(res,Query(x << 1 | 1,mid + 1,r,L,R));
	return res;
}

void del(int x,int l,int r,int pos,int val){
	que[x].del(val);
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(pos <= mid) del(x << 1,l,mid,pos,val);
	else del(x << 1 | 1,mid + 1,r,pos,val);
}

void insert(int x,int l,int r,int pos,int val){
	que[x].push(val);
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(pos <= mid) insert(x << 1,l,mid,pos,val);
	else insert(x << 1 | 1,mid + 1,r,pos,val);
}

int find(int x){
	int l = 1,r = n,res = 0;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(A[mid].y <= x) res = mid,l = mid + 1;
		else r = mid - 1;
	}
	return res;
}

int main(){
	read(n),read(m);
	for(int i = 1;i <= n;i++) read(A[i].x),read(A[i].y),A[i].id = i;
	
	std :: sort(A + 1,A + n + 1);
	for(int i = 1;i <= n;i++) rnk[A[i].id] = i;
	
	build(1,1,n);

	while(m--){
		int opt,pos,p,w,x;
		read(opt);
		if(opt == 1){
			read(pos),read(w),read(p);
			while(1){}
		}
		if(opt == 2){
			int k; int ans = 0;
			read(k);
			while(1){				
				int pos = find(k);
				if(!pos) break;
				int val = Query(1,1,n,1,pos);
				ans += (k / val) * val; k %= val;
			}
			printf("%d\n",ans);
		}
	}

	return 0;
}
