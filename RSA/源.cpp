#include "LargeInt.h"
#include "Generator.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

#include <gmp.h>
//#pragma  comment(lib,"libgmp.lib")

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

void test_EGCD(){
	egcd(3, 20);
	egcd(13, 2436);
	egcd(4, 1326);
}

void test_Multi(){
	int i = 0;
	LargeInt tmp = LargeInt(3);
	while (i < 10){
		tmp = tmp * tmp;
		i += 1;
	}
	LargeInt tmp2(1);
	LargeInt t(3);
	for(int i = 0;i < 1024;i++)
		tmp2 = tmp2 * t;
	//cout<<tmp<<endl;
	//cout<<tmp2<<endl;
	cout<<"test_Multi\t" << tmp2 - tmp << endl;
}

void test_Multi2(){
	LargeInt tmp1(100);
	LargeInt tmp2;
	cout << tmp1 * tmp2<<endl;
}

void test_Div(){
	cout<<"**********test_Div**********"<<endl;
	int i = 0;
	LargeInt tmp = LargeInt(3);
	while (i < 12){
		tmp = tmp * tmp;
		i += 1;
	}
	LargeInt tmp2(1);
	LargeInt t(3);
	for(int i = 0;i < 100;i++)
		tmp2 = tmp2 * t;
	tmp2 = tmp2 + 1;
	

	//LargeInt n(1234535);
	//cout<<"test_Div\t"<<tmp2.module(n)<<endl;

	//cout<<tmp<<endl;
	tmp2 = LargeInt(0) - tmp2;

	LargeInt res = tmp / tmp2;

	//cout<<"tmp\t"<<tmp<<endl;
	//cout<<"mul\t"<<(tmp2 * res) / 16<<endl;
	//cout<<"tmp2\t"<<tmp2<<endl;
	//cout<<"res\t"<<res<<endl;

	cout<<"divided\t"<<tmp2<<endl;
	cout<<"posi\t"<<(tmp - tmp2 * res)<<endl;
	cout<<"nega\t"<<(tmp - tmp2 * (res + 1))<<endl;
	cout<<"**********test_Div**********"<<endl;
}

//void test_Module(){
//	//cout<<"**********test_Module**********"<<endl;
//	int i = 0;
//	LargeInt tmp = LargeInt(3);
//	while (i < 9){
//		tmp = tmp * tmp;
//		i += 1;
//	}
//	LargeInt n(1234535);
//
//	cout<<tmp<<endl;
//	tmp = tmp.module(n);
//	cout<<tmp<<endl;
//
//	LargeInt t1(3);
//	LargeInt t2(512);
//	LargeInt tmp2 = exponent(t1, t2, n);
//
//	cout<<tmp2<<endl;
//
//	cout<<"**********test_Module\t"<< tmp2 - tmp <<"\t**********"<<endl;
//}

void test_BinaryStr1(){
	LargeInt tmp = LargeInt(3);
	int i = 0;
	while (i < 10){
		tmp = tmp * tmp;
		i += 1;
	}

	LargeInt res1;
	for(int i = 0;i < 1000;i++)
		res1 = res1 + tmp;

	string s = res1.toBinString();
	LargeInt res2;
	for(char c : s){
		res2 = (res2 * 2) + (c - '0');
	}
	//cout<<"res1\t"<<res1<<endl;
	//cout<<"res2\t"<<res2<<endl;
	cout<<"test_BinaryStr\t"<<(res2 - res1)<<endl;
}

void test_BinaryStr2(){
	LargeInt tmp(1024);
	cout<<tmp.toBinString()<<endl;
}

void test_Minus(){
	LargeInt tmp1(0);
	LargeInt tmp2(0);

	cout<<tmp1 - tmp2<<endl;
}

void test_random(){
	/*for(int i = 0;i < 10;i++)
		cout<<rand()<<endl;
	cout<<RAND_MAX<<endl;*/
	LargeInt res;
	for (int i = 0;i < 10;i++){
		res.generateRandom(512);
		cout<<"********"<<i<<"****************"<<endl;
		cout<<res<<endl;
		//cout<<"size"<<res.data.size()<<endl;
	}
}

void test_gene(){
	LargeInt res = primeGenerate(1024);
	cout<<res<<endl;
	//LargeInt res(263167);
	//cout<<exponent(LargeInt(3), res - 1, res)<<endl;
	//cout<<millerRabin(res, 0, 0)<<endl;
}

void test_Chinese(){
	/*string str;
	cin >> str;
	cout<<"输出"<<endl;
	cout<<str<<endl;
	cout<<str.length()<<endl;
	for(int i = 0;i < str.length();i++)
		cout<<(unsigned int)str[i]<<endl;
*/
	string tmp(6, '0');
	tmp[0] = (unsigned int)4294967254;
	tmp[1] = (unsigned int)4294967248;
	tmp[2] = (unsigned int)4294967246;
	tmp[3] = (unsigned int)4294967236;
	tmp[4] = (unsigned int)111;
	tmp[5] = (unsigned int)107;
	cout<<tmp<<endl;
}

void test_gmp(){
	LargeInt tmp = LargeInt(100);
	int i = 0;
	while (i < 5){
		tmp = tmp * tmp;
		i += 1;
	}
	cout<<tmp<<endl;

	mpz_t t;
	string str = tmp.toString();
	const char *cstr = str.c_str();
	mpz_init_set_str(t, cstr, 16);

	char* buff = new char[1000];
	gmp_sprintf(buff, "%Zx\n", t);
	string retStr(buff);

	cout<<retStr<<endl;

	mpz_t a, b, c;  
	mpz_init(a);  
	mpz_init_set_str(b, "abcde", 16);  
	mpz_init_set_str(c, "-1a0", 16); 
	mpz_fdiv_q (a, b, c);
	gmp_printf("%Zx\n", a);

	//mpz_t t; //mpz_t 为GMP内置大数类型
	//mpz_init(t); //大数t使用前要进行初始化，以便动态分配空间
	//mpz_ui_pow_ui(t, 2, 2000); //GMP所有函数基本都是以mpz打头
	//gmp_printf("2^100=%Zd\n", t); //输出大数，大数的格式化标志为%Zd
	//mpz_clear(t);
}

void test(){
	LargeInt res(1234567);
	res = LargeInt(0) - res;
	cout<<res<<endl;
	LargeInt tmp;
	tmp.transform(res.toString());
	cout<<tmp<<endl;
}

void test_prime(){
	LargeInt res;
	while(true){
		res = primeGenerate(2048);
		mpz_t a;
		mpz_init_set_str(a, res.toString().c_str(), 16);  
		cout<<"isPrime\t"<<mpz_probab_prime_p(a, 10)<<endl;
		_sleep(500);
	}
}

int main(){
	srand(time(0));

	//test();

	//test_gmp();

	//test_gene();
	test_prime();

	//test_random();

	//test_EGCD();

	//test_Multi();
	//test_Multi2();

	//test_Div();

	//test_Module();

	//test_BinaryStr2();

	//test_Minus();

	//test_Chinese();

	system("Pause");
	return 0;
}