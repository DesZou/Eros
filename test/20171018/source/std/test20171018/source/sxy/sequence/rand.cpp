//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<ctime>
using namespace std;
const int n=200000,f=100,q=200000;
int m,k;

int main() {
	freopen("sequence.in","w",stdout);
	srand((unsigned)time(NULL));
	m=rand()%f+1;k=rand()%(n/4)+1;
	cout<<n<<" "<<m<<" "<<k<<"\n";
	int x,y;
	for(int i=1;i<=n;++i) {
		x=rand()%f+1;
		cout<<x<<" ";
	}
	cout<<"\n"<<q<<"\n";
	for(int i=1;i<=q;++i) {
		x=rand()%n+1;
		if(x!=n) y=rand()%(n-x+1); else y=0;
		cout<<x<<" "<<x+y<<"\n";
	}
	return 0;
}

