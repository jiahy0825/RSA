#include "Crypt.h"

void Crypt::generateKey(int bits){
	this->bits = bits;
	this->p = primeGenerate(bits);
	this->q = primeGenerate(bits);
	this->n = this->p * this->q;
	this->phi = (this->p - 1) * (this->q - 1);
}

//Bezout Therom
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
	return e;
}

void Crypt::generateED(LargeInt& tmp){
	this->e = tmp;
	LargeInt one = e_gcd(this->e, this->phi);
	if(one != 1){
		cout<< "e 不可逆, gcd:\t" << one << endl;
	}else{
		//cout<< "生成完毕 d:\t" << this->d << endl;
	}
}

string encode(string& str){
	
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

