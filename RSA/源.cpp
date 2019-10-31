#include "LargeInt.h"
#include "Generator.h"

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

	LargeInt res = tmp / tmp2;

	//cout<<tmp<<endl;
	//cout<<tmp2<<endl;
	//cout<<res<<endl;

	cout<<"divided\t"<<tmp2<<endl;
	cout<<"posi\t"<<(tmp - tmp2 * res)<<endl;
	cout<<"nega\t"<<(tmp - tmp2 * (res + 1))<<endl;
	cout<<"**********test_Div**********"<<endl;
}

void test_Module(){
	//cout<<"**********test_Module**********"<<endl;
	int i = 0;
	LargeInt tmp = LargeInt(3);
	while (i < 9){
		tmp = tmp * tmp;
		i += 1;
	}
	LargeInt n(1234535);

	////cout<<tmp<<endl;
	tmp = tmp.module(n);
	//cout<<tmp<<endl;

	LargeInt t1(3);
	LargeInt t2(512);
	LargeInt tmp2 = exponent(t1, t2, n);

	//cout<<tmp2<<endl;

	cout<<"**********test_Module\t"<< tmp2 - tmp <<"\t**********"<<endl;
}

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

int main(){

	//test_EGCD();

	//test_Multi();
	//test_Multi2();

	//test_Div();

	//test_Module();

	//test_BinaryStr2();

	//test_Minus();

	system("Pause");
	return 0;
}