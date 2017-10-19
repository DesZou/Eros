//by Saramanda
#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For(i,_beg,_end) for(register int i=(_beg),i##end=(_end);i<=i##end;++i)
#define Rep(i,_beg,_end) for(register int i=(_beg),i##end=(_end);i>=i##end;--i)

template<typename T>T Max(const T &x,const T &y){return x<y?y:x;}
template<typename T>T Min(const T &x,const T &y){return x<y?x:y;}
template<typename T>int chkmax(T &x,const T &y){return x<y?(x=y,1):0;}
template<typename T>int chkmin(T &x,const T &y){return x>y?(x=y,1):0;}
template<typename T>inline void read(T &x){
	T f=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(x=0;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
	x*=f;
}

typedef long long LL;
const int maxn=100010;
struct node{
	int w,c;
	bool operator<(const node &y)const{
		if(w==y.w)return c<y.c;
		return w>y.w;
	}
	bool operator>(const node &y)const{
		return y<*this;
	}
	node(){w=0;c=0x7fffffff;}
};
struct Input{
	int op,x,a,b;
}q[maxn];
int n,m,w[maxn],c[maxn],cnt,mp[maxn<<1];
multiset<node> a[maxn<<1];

node mk(const int &w,const int &c){
	node x;
	x.w=w;x.c=c;
	return x;
}
void insert(int x,const node &val){
	for(;x<=cnt;x+=x&-x) a[x].insert(val);
}
void erase(int x,const node &val){
	for(;x<=cnt;x+=x&-x) a[x].erase(a[x].find(val));
}
node query(int x){
	node res;
	for(;x;x-=x&-x) if(!a[x].empty())chkmin(res,*a[x].begin());
	return res;
}

int main(){
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	read(n);read(m);
	For(i,1,n){
		read(w[i]);read(c[i]);
		mp[++cnt]=c[i];
	}
	int op,x,a,b;
	For(i,1,m){
		read(op);read(x);
		if(op==1){
			read(a);read(b);
			mp[++cnt]=b;
		}
		q[i].op=op;q[i].x=x;
		q[i].a=a;q[i].b=b;
	}
	sort(mp+1,mp+cnt+1);
	cnt=unique(mp+1,mp+cnt+1)-mp-1;
	For(i,1,n){
		register int pos=lower_bound(mp+1,mp+cnt+1,c[i])-mp;
		insert(pos,mk(w[i],c[i]));
	}
	For(i,1,m){
		op=q[i].op;x=q[i].x;
		a=q[i].a;b=q[i].b;
		if(op==1){
			register int pos=lower_bound(mp+1,mp+cnt+1,c[x])-mp;
			erase(pos,mk(w[x],c[x]));
			w[x]=a;c[x]=b;
			pos=lower_bound(mp+1,mp+cnt+1,b)-mp;
			insert(pos,mk(a,b));
		}
		else{
			register int pos=upper_bound(mp+1,mp+cnt+1,x)-mp-1;
			node temp=query(pos);
			LL ans=0;
			while(x>=temp.c){
				ans+=(LL)x/temp.c*temp.w;
				x%=temp.c;
				pos=upper_bound(mp+1,mp+cnt+1,x)-mp-1;
				temp=query(pos);
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
