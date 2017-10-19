//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<ctime>
using namespace std;
const int n=100000,m=100000,q=100000;

int main() {
	srand((unsigned)time(NULL));
	freopen("segment.in","w",stdout);
	cout<<n<<" "<<m<<" "<<q<<"\n";
	for(int i=1;i<=n;++i) cout<<rand()<<" ";
	cout<<"\n";
	int l,r,op,x;
	for(int i=1;i<=m;++i) {
		x=rand();
		l=rand()%n+1;r=l==n? 0 : rand()%(n-l+1);
		op=rand()%2+1;
		cout<<op<<" "<<l<<" "<<r<<" "<<x<<"\n";
	}
	for(int i=1;i<=q;++i) {
		l=rand()%n+1;r=l==n? 0 : rand()%(n-l+1);
		cout<<l<<" "<<r<<"\n";
	}
	return 0;
}

