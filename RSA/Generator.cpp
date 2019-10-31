#include "Generator.h"

LargeInt exponent(LargeInt& a, LargeInt& b, LargeInt& n){
	LargeInt res(1);
	string str = b.toBinString();
	int i = 0;
	for(char c : str){
		res = (res * res).module(n);
		if(c == '1'){
			res = (res * a).module(n);
		}
	}
	return res;
}
