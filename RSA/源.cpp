#include "LargeInt.h"

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void egcd(int a, int b){
	int A = a;
	int B = b;
	int u = 1;
	int e = 0;
	int v = 0;
	int f = 1;
	int t = 0;
	int q = 0;
	while(b != 0){
		q = a / b;
		t = a - q * b;
		a = b;
		b = t;
		t = u - q * e;
		u = e;
		e = t;
		t = v - q * f;
		v = f;
		f = t;
	}
	cout << a << "=" << u << "\t*\t" << A << "\t+\t" << v << "\t*\t" << B << endl;
	
}


int main(){
	egcd(3, 20);
	egcd(13, 2436);
	egcd(4, 1326);

	//LargeInt res = LargeInt(225);
	int i = 0;
	//while (i < 100){
	//	//cout<<res.toString()<<endl;
	//	res = res * 16;
	//	i += 1;
	//}

	//res = res + 1;

	i = 0;
	LargeInt tmp = LargeInt(3);
	while (i < 10){
		tmp = tmp * tmp;
		i += 1;
	}

	//cout<<tmp.toString()<<endl;

	LargeInt res1;
	res1 = tmp * 10;

	LargeInt res2;
	for(int i = 0;i < 10;i++)
		res2 = res2 + tmp;

	cout<<res1<<endl<<res2<<endl;

	cout<<(res1 - res2)<<endl;

	system("Pause");
	return 0;
}