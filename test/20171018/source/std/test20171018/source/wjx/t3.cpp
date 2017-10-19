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
int n,m,jg[maxn],jz[maxn];

void read(int &x) {
    int ret=0,f=1; char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    for(;ch>='0'&&ch<='9';ch=getchar()) ret=ret*10+ch-'0';
    x=ret;
}

#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
int sg[maxn<<2],id[maxn<<2];
void update(int x,int l,int r,int pos,int v) {
    if(l==r) {sg[x]=v; id[x]=pos; return;}
    if(pos<=mid) update(lc,l,mid,pos,v);
    else update(rc,mid+1,r,pos,v);
    if(sg[lc]>sg[rc]) id[x]=id[lc]; 
    else id[x]=id[rc];
    sg[x]=max(sg[lc],sg[rc]);
}

int qry(int x,int l,int r,int ql,int qr,int &v) {
    if(l>=ql&&r<=qr) { v=sg[x]; return id[x];}
    if(qr<=mid) return qry(lc,l,mid,ql,qr,v);
    else if(ql>mid) return qry(rc,mid+1,r,ql,qr,v);
    int tp1,tp2,r1,r2;
    r1=qry(lc,l,mid,ql,qr,tp1); 
	r2=qry(rc,mid+1,r,ql,qr,tp2);
	v=max(tp1,tp2);
	return v==tp1?r1:r2;
}

void init() {
    read(n); read(m);
}

void work() {

}

int main()
{
	//freopen("shopping.in","r",stdin);
	//freopen("shopping.out","w",stdout);
	init();
	work();
	return 0;
}

