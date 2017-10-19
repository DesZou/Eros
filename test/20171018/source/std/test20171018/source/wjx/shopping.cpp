//Twenty
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<queue>
const int maxn=100005;
using namespace std;
typedef long long LL;
int n,m,jg[maxn],jz[maxn],p[maxn][4],ls[maxn],sz,szz;

void read(int &x) {
    int ret=0,f=1; char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    for(;ch>='0'&&ch<='9';ch=getchar()) ret=ret*10+ch-'0';
    x=ret*f;
}

#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
int sg[maxn<<2],id[maxn<<2];
void update(int x,int l,int r,int pos,int v) {
    if(l==r) {sg[x]=v; id[x]=l; return;}
    if(pos<=mid) update(lc,l,mid,pos,v);
    else update(rc,mid+1,r,pos,v);
    if(sg[lc]>sg[rc]) id[x]=id[lc]; 
    else id[x]=id[rc];
    sg[x]=max(sg[lc],sg[rc]);
}

int qry(int x,int l,int r,int ql,int qr,int &v) {
    if(ls[l]>=ql&&ls[r]<=qr) { v=sg[x]; return id[x];}
    else if(l==r) return 0;
    if(qr<=ls[mid]) return qry(lc,l,mid,ql,qr,v);
    else if(ql>ls[mid]) return qry(rc,mid+1,r,ql,qr,v);
    int tp1=0,tp2=0,r1,r2;
    r1=qry(lc,l,mid,ql,qr,tp1); 
	r2=qry(rc,mid+1,r,ql,qr,tp2);
	v=max(tp1,tp2);
	return v==tp1?r1:r2;
}

void init() {
    read(n); read(m);
	for(int i=1;i<=n;i++) {
	    read(jz[i]);
		read(jg[i]);
		ls[++sz]=jg[i];
	}
	for(int i=1;i<=m;i++) {
	    read(p[i][0]); read(p[i][1]);
	    if(p[i][0]==1) {
	    	read(p[i][2]);
		    read(p[i][3]);
		    ls[++sz]=p[i][3];
		}
	}
}

struct node {
	int id,v;
	node(int id,int v):id(id),v(v){}
    friend bool operator <(const node&A,const node&B) {
	    return A.v<B.v;
 	}
};
priority_queue<node>que[maxn];

void work() {
    sort(ls+1,ls+sz+1);
    int tpsz=unique(ls+1,ls+sz+1)-(ls+1);
    sz=tpsz;
    for(int i=1;i<=n;i++) {
    	int x=lower_bound(ls+1,ls+sz+1,jg[i])-ls;
	    que[x].push(node(i,jz[i])); 
	}
	for(int i=1;i<=sz;i++) {
	    if(!que[i].empty() ) {
		    node x=que[i].top();
		    update(1,1,sz,i,x.v);
		}
	}
	for(int i=1;i<=m;i++) {
	    if(p[i][0]==1) {
	    	int x=p[i][1],jzz=p[i][2],jgg=p[i][3];
	    	int t=lower_bound(ls+1,ls+sz+1,jg[x])-ls;
	    	node a=que[t].top();
	    	if(a.id==x&&a.v==jz[x]) {
			    que[t].pop();
			    int now=0;
			    while(!que[t].empty()) {
				    a=que[t].top();
				    if(jz[a.id]!=a.v) que[t].pop();
				    else {
				    	now=a.v;
					    break;
				    }
				}
			    update(1,1,sz,t,now);
			}
	    	jg[x]=jgg; jz[x]=jzz;
	    	t=lower_bound(ls+1,ls+sz+1,jg[x])-ls;
	    	if(que[t].empty()) update(1,1,sz,t,jz[x]);
	    	if(!que[t].empty()) {
			    node a=que[t].top();
			    if(a.v<jz[x]) {update(1,1,sz,t,jz[x]);}
			}
	    	que[t].push(node(x,jz[x]));
		}
		else {
			LL ans=0;
		    int now=p[i][1],tpv=0;
		    int q=qry(1,1,sz,0,now,tpv);
		    while(q&&tpv) {
		    	int gs=now/ls[q];
			    ans+=tpv*gs;
			    now=now-gs*ls[q];
			    q=qry(1,1,sz,0,now,tpv);
			}
			printf("%lld\n",ans);
		}
	}
}

int main()
{
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	init();
	work();
	return 0;
}
