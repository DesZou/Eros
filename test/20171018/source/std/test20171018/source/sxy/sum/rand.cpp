//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<ctime>
using namespace std;
#define ll long long
const int n=100000;
ll mod,x;

int main() {
	freopen("sum.in","w",stdout);
	srand((unsigned)time(NULL));
	mod=rand()*rand();
	cout<<n<<" "<<mod<<"\n";
	for(int i=1;i<=n;++i) {
		x=rand(); cout<<x<<" ";
	}
	cout<<"\n";
	return 0;
}

