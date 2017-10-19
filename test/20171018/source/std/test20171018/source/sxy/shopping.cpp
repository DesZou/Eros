//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<queue>
#include<set>
using namespace std;
#define ll long long
const int maxn=2e5+10;
ll n,m,w[maxn],p[maxn],f[maxn],tot,qpos,qx,ans;

ll aa;char cc;
ll read() {
	aa=0;cc=getchar();
	while(cc<'0'||cc>'9') cc=getchar();
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa;
}

struct Node{
	int pos;
	Node(){}
	Node(int pos):pos(pos){}
	bool operator < (const Node& a) const{
		return w[pos] < w[a.pos];
	}
};
priority_queue<Node> G;

int main() {
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;++i) w[i]=read(),p[i]=read();
	int op,pos,pp;
	for(int i=1;i<=m;++i) {
		op=read();
		while(!G.empty()) G.pop();
		if(op==1) {
			pos=read();
			w[pos]=read();
			p[pos]=read();
		}
		else {
			pp=read(); ans=0;
			for(int i=1;i<=n;++i) if(p[i]<=pp) G.push(Node(i));
			while(pp&&!G.empty()) {
				while(!G.empty()&&p[G.top().pos]>pp) G.pop();
				if(!G.empty()) ans+=w[G.top().pos],pp-=p[G.top().pos];
			}
			printf("%lld\n",ans);
		}
	}
	fclose(stdin);fclose(stdout);
	return 0;
}

