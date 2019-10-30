#include "Generator.h"

LargeInt exponent(LargeInt& a, LargeInt& b, LargeInt& n){
	LargeInt res(0);
	string str = b.toBinString();
	for(char c : str){
		res = (res * res).module(n);
		if(c == '1'){
			res = (res * a).module(n);
		}
	}
	return res;
}