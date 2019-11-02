#ifndef _CRYPT_H
#define _CRYPT_H
#include "Generator.h"
#include "LargeInt.h"
#include "gmp.h"

class Crypt{
private:
	LargeInt p;
	LargeInt q;
	LargeInt n;
	LargeInt phi;
	LargeInt e;
	LargeInt d;
	int bits;

public:
	// ����λ������p q n phi
	void generateKey(int bits);

	void generateED(LargeInt& tmp);

	LargeInt e_gcd(LargeInt e, LargeInt phi);

	string encode(string& str);

	string decode(string& str);

	// ������Կ���ɽӿ�
	void setpqe(int p, int q, int e);

	void output();

};

#endif