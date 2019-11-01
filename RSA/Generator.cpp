#include "Generator.h"

LargeInt exponent(LargeInt& a, LargeInt& b, LargeInt& n){
	//cout<<"******exponent*********"<<endl;
	LargeInt res(1);
	string str = b.toBinString();
	int i = 0;
	for(char c : str){
		res = (res * res).module(n);
		if(c == '1'){
			res = (res * a).module(n);
		}
		cout<<c;
	}
	//cout<<"******exponent*********"<<endl;
	return res;
}

bool witness(LargeInt& a, LargeInt& n){
	LargeInt minusOne;
	minusOne = n - 1;
	LargeInt tmp(2);
	int t = 0;
	cout<<"witness init finish"<<endl;
	while(minusOne.module(tmp) == 0){
		tmp = tmp * 2;
		t += 1;
	}
	//cout<<"witness while finish t number:\t"<<t<<endl;
	tmp = tmp / 2;
	LargeInt u = minusOne / tmp;
	cout<<"witness exponent begin a:\t"<<a<<endl;
	cout<<"witness exponent begin u:\t"<<u<<endl;
	cout<<"witness exponent begin n:\t"<<n<<endl;

	LargeInt x0 = exponent(a, u, n);

	cout<<"x0\t"<<x0<<endl;
	LargeInt x1 = x0;
	//cout<<"witness for begin x1:\t"<<x1<<endl;
	for(int i = 0;i < t;i++){
		x1 = (x0 * x0).module(n);
		if(x1 == 1 && x0 != 1 && x0 != minusOne){
			cout<<x0<<endl;
			cout<<x1<<endl;
			return true;
		}
		x0 = x1;
		//cout<<"x1"<<x1<<endl;
	}
	//cout<<"witness for finish x1:\t"<<x1<<endl;
	cout<<"x1\t"<<x1<<endl;
	if(x1 != 1)
		return true;
	return false;
}

// s为循环次数
//bool millerRabin(LargeInt& n, int bits, int s){
//	LargeInt tmp;
//	for(int i = 0;i < s;i++){
//		tmp.generateRandom(bits - 1);
//		if(witness(tmp, n)){
//			return true;
//		}
//	}
//	return false;
//}

bool millerRabin(LargeInt& n, int bits, int s){
	LargeInt tmp;
	int arr[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
	for(int i = 0;i < 13;i++){
		//tmp.generateRandom(bits - 1);
		tmp = LargeInt(arr[i]);
		if(witness(tmp, n)){
			return true;
		}
	}
	return false;
}

LargeInt primeGenerate(int bits){
	LargeInt res;
	res.generateRandom(bits);
	int i = 0;
	while(millerRabin(res, bits, 1)){
		cout<<"*********** gene iter\t" << i++ << "\t*************"<<endl;
		res.generateRandom(bits);
		_sleep(1000);
	}
	return res;
}