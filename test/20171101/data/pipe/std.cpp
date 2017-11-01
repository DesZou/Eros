#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define FR first
#define SE second

using namespace std;

typedef pair<int,int> pr;
typedef long long ll;

struct Edge {
  int s,t,v,id;
  Edge() {}
  Edge(int a,int b,int c,int d):s(a),t(b),v(c),id(d) {}
  bool operator < (const Edge & b) const {return v<b.v;}
};

Edge e[200005];
bool in[200005];
int id[200005];

namespace SETS {

int fa[200005];

void init(int n) {
  for(int i=1;i<=n;i++) fa[i]=i;
}

int find_father(int x) {
  return (fa[x]==x)?x:fa[x]=find_father(fa[x]);
}

bool merge(int x,int y) {
  x=find_father(x);y=find_father(y);
  if (x==y) return 0;
  fa[x]=y;
  return 1;
}

}

vector <pr> son[200005];

namespace MST {

ll Kruskal(int m) {
  sort(e+1,e+m+1);
  ll sum=0;
  for(int i=1;i<=m;i++)
    if (SETS::merge(e[i].s,e[i].t)) {
    	in[e[i].id]=1;
    	int x=e[i].s,y=e[i].t;
    	son[x].push_back(pr(y,e[i].v));
    	son[y].push_back(pr(x,e[i].v));
    	sum+=e[i].v;
	}
	else id[e[i].id]=i;
  return sum;
}

}

namespace Tree {

int fa[200005][20],dep[200005];
int maxn[200005][20];

void dfs(int x) {
  for(int i=0;i<son[x].size();i++)
    if (son[x][i].FR!=fa[x][0]) {
    	int u=son[x][i].FR;
    	fa[u][0]=x;maxn[u][0]=son[x][i].SE;
    	dep[u]=dep[x]+1;
    	for(int j=1;j<20;j++) {
    		fa[u][j]=fa[fa[u][j-1]][j-1];
    		maxn[u][j]=max(maxn[u][j-1],maxn[fa[u][j-1]][j-1]);
		}
		dfs(u);
	}
}

int query(int x,int y) {
  int ans=0;
  if (dep[x]<dep[y]) swap(x,y);
  int d=dep[x]-dep[y];
  for(int i=0;i<20;i++)
    if (d&(1<<i)) {
    	ans=max(ans,maxn[x][i]);
    	x=fa[x][i];
	}
  if (x==y) return ans;
  for(int i=19;i>=0;i--)
    if (fa[x][i]!=fa[y][i]) {
    	ans=max(ans,max(maxn[x][i],maxn[y][i]));
    	x=fa[x][i];
    	y=fa[y][i];
	}
  ans=max(ans,max(maxn[x][0],maxn[y][0]));
  return ans;
}

}

int main() {
  freopen("10.in","r",stdin);
  freopen("10.out","w",stdout);
  int n,m;
  scanf("%d%d",&n,&m);
  SETS::init(n);
  for(int i=1;i<=m;i++) {
  	int x,y,z;
  	scanf("%d%d%d",&x,&y,&z);
  	e[i]=Edge(x,y,z,i);
  }
  ll sum=MST::Kruskal(m);
  Tree::dfs(1);
  for(int i=1;i<=m;i++)
    if (in[i]) printf("%lld\n",sum);
    else printf("%lld\n",sum-Tree::query(e[id[i]].s,e[id[i]].t)+e[id[i]].v);
  return 0;
}
