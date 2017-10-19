#include<bits/stdc++.h>
using namespace std ;

int main() {
	
	int T = 0 ;
	
	system ("g++ -g -o 1 data.cpp") ;
	system ("g++ -g -o 2 t.cpp") ;
	system ("g++ -g -o 3 std.cpp") ;
	
	bool f = false ;
	
	while (!f) {
		
		system ("./1") ;
		system ("./2") ;
		system ("./3") ;
		
		f = system ("diff t.out std.out") ;
		
		printf ("%d", ++T) ; puts (f? "WA": "AC") ;
	}
	
	return 0 ;
}
