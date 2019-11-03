#include "stdafx.h"

#include "Crypt.h"
#include "Generator.h"

#include <ctime>

void Crypt::generateKey(int bits){
	clock_t start, end;

	start = clock();

	this->bits = bits;
	this->p = primeGenerate(bits);
	this->q = primeGenerate(bits);
	this->n = this->p * this->q;
	this->phi = (this->p - 1) * (this->q - 1);

	end = clock();

	cout<<"time\t"<<(end - start)<<endl;

}

// Bezout Therom
// Update d
LargeInt Crypt::e_gcd(LargeInt e, LargeInt phi){
	this->d = LargeInt(1);
	LargeInt g(0);
	LargeInt v(0);
	LargeInt f(1);
	LargeInt t(0);
	LargeInt q(0);
	while(phi != 0){
		q = e / phi;
		t = e - q * phi;
		e = phi;
		phi = t;
		t = this->d - q * g;
		this->d = g;
		g = t;
		t = v - q * f;
		v = f;
		f = t;
	}
	if(this->d < 0){
		this->d = this->d + this->phi;
	}
	return e;
}

void Crypt::generateED(LargeInt& tmp){
	this->e = tmp;
	//this->e.generateRandom(28);
	LargeInt one = e_gcd(this->e, this->phi);
	while(one != 1){
		this->e.generateRandom(16);
		this->e = this->e + 12340;
		one = e_gcd(this->e, this->phi);
	}
	//if(one != 1){
	//	//cout<< "e 不可逆, gcd:\t" << one << endl;
	//}else{
	//	//cout<< "生成完毕 d:\t" << this->d << endl;
	//}
}

string c2str(char c){
	char ch[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	string res = "";
	res += ch[((int)c & 0xf0000000) >> 28];
	res += ch[((int)c & 0x0f000000) >> 24];
	res += ch[((int)c & 0x00f00000) >> 20];
	res += ch[((int)c & 0x000f0000) >> 16];
	res += ch[((int)c & 0x0000f000) >> 12];
	res += ch[((int)c & 0x00000f00) >> 8];
	res += ch[((int)c & 0x000000f0) >> 4];
	res += ch[(int)c & 0x0000000f];
	return res;
}

string Crypt::encode(string& str){
	string codeStr = "";
	for(char c : str){
		codeStr += c2str(c);
	}
	/*cout<<"origin string \t"<<codeStr<<"\t"<<codeStr.length()<<endl;*/
	LargeInt num;
	num.transform(codeStr);
	LargeInt code;
	code = exponent2(num, this->e, this->n);
	
	string strtmp = code.toString();
	//cout<<strtmp<<"\t"<<strtmp.length()<<endl;
	return strtmp;
	
	/*return code.toString();*/
}

u32 str2u32(string& str){
	u32 res = 0;
	for(char c : str){
		if(c >= '0' && c <= '9'){
			res = (res << 4) | (c - '0');
		}else{
			res = (res << 4) | (c - 'a' + 10);
		}
	}
	return res;
}

string str2word(string& str){
	int len = (str.length() + 7) / 8;
	if(len * 8 > str.length()){
		str = string(len * 8 - str.length(), '0') + str;
		//cout<<"补位\t"<<str<<endl;
	}
	string res(len, '0');
	for(int i = 0;i < len;i++){
		res[i] = str2u32(str.substr(i * 8, 8));
	}
	return res;
}

void egcd(LargeInt a, LargeInt b, LargeInt& N1, LargeInt& N2){
	LargeInt u(1);
	LargeInt e(0);
	LargeInt v(0);
	LargeInt f(1);
	LargeInt t(0);
	LargeInt q(0);
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
	N1 = u;
	N2 = v;
}

LargeInt expoCRT(LargeInt& x, LargeInt& d, LargeInt& n, LargeInt& p, LargeInt& q){
	LargeInt a = exponent2(x, d.module(p - 1), p);
	LargeInt b = exponent2(x, d.module(q - 1), q);
	LargeInt N1, N2;
	egcd(q, p, N1, N2);
	LargeInt y = (a * q * N1 + b * p * N2).module(n);
	return y;
}

string Crypt::decode(string& str){
	LargeInt num;
	num.transform(str);
	LargeInt code;
	//code = exponent2(num, this->d, this->n);
	code = expoCRT(num, this->d, this->n, this->p, this->q);
	string res = code.toString();
	res = str2word(res);
	return res;
}

void Crypt::setpqe(int p, int q, int e){
	this->p = LargeInt(p);
	this->q = LargeInt(q);
	this->e = LargeInt(e);

	this->n = this->p * this->q;
	this->phi = (this->p - 1) * (this->q - 1);

	this->generateED(this->e);
}

void Crypt::output(){
	cout<<"*********** output ************"<<endl;
	cout << "  p:\t" << this->p << endl;
	cout << "  q:\t" << this->q << endl;
	cout << "  n:\t" << this->n << endl;
	cout << "phi:\t" << this->phi << endl;
	cout << "  e:\t" << this->e << endl;
	cout << "  d:\t" << this->d << endl;
	cout<<"*********** output ************"<<endl;
}

