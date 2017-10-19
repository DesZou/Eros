//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
const int maxn=3e5+10;
int n,m,ans;

int aa;char cc;
int read() {
	aa=0;cc=getchar();
	while(cc<'0'||cc>'9') cc=getchar();
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa;
}

struct Node{
	int x,y;
}node[maxn];

bool cmp(const Node& a,const Node& b) {
	return a.x < b.x;
}

struct LT{
	int x;
	LT(){}
	LT(int x):x(x){}
	bool operator < (const LT& b) const{
		return x > b.x;
	}
};
priority_queue<LT> G;

int main() {
	freopen("work.in","r",stdin);
	freopen("work.out","w",stdout);
	n=read(); m=read();
	for(int i=1;i<=n;++i) {
		node[i].x=read();
		node[i].y=read()+node[i].x;
	}
	sort(node+1,node+n+1,cmp);
	for(int i=1;i<=n;++i) {
		while(!G.empty()&&node[i].x-G.top().x>m) G.pop();
		if(!G.empty()&&node[i].x>=G.top().x) {
			ans++;G.pop();
		}
		G.push(LT(node[i].y));
	}
	printf("%d",ans);
	fclose(stdin);fclose(stdout);
	return 0;
}

