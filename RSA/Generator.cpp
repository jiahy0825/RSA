#include "Generator.h"
#include <gmp.h>
#include <vector>

LargeInt exponent2(LargeInt& a, LargeInt& b, LargeInt& n){
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

bool witness2(LargeInt& a, LargeInt& n){
	LargeInt minusOne;
	minusOne = n - 1;
	LargeInt tmp(2);
	int t = 0;
	while(minusOne.module(tmp) == 0){
		tmp = tmp * 2;
		t += 1;
	}
	tmp = tmp / 2;
	LargeInt u = minusOne / tmp;

	LargeInt x0 = exponent2(a, u, n);
	LargeInt x1 = x0;
	for(int i = 0;i < t;i++){
		x1 = (x0 * x0).module(n);
		if(x1 == 1 && x0 != 1 && x0 != minusOne){
			cout<<x0<<endl;
			cout<<x1<<endl;
			return true;
		}
		x0 = x1;
	}
	if(x1 != 1)
		return true;
	return false;
}

bool millerRabin2(LargeInt& n, int bits, int s){
	LargeInt tmp;
	int arr[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
	for(int i = 0;i < 25;i++){
		tmp = LargeInt(arr[i]);
		if(witness2(tmp, n)){
			return true;
		}
	}
	return false;
}

LargeInt primeGenerate2(int bits){
	LargeInt res;
	res.generateRandom(bits);
	int i = 0;
	while(millerRabin2(res, bits, 1)){
		/*cout<<"*********** gene iter\t" << i++ << "\t*************"<<endl;*/
		res.generateRandom(bits);
	}
	return res;
}


void exponent(mpz_t& res, mpz_t& a, mpz_t& b, mpz_t& n){
	mpz_powm_sec(res, a, b, n);
}

bool witness(mpz_t& a, mpz_t& n){
	mpz_t minusOne;
	mpz_t zero;
	mpz_t one;
	mpz_t two;

	mpz_t tmp;
	mpz_t mid;
	mpz_init(minusOne);
	mpz_init(mid);
	mpz_init_set_str(tmp, "1", 10); 
	mpz_init_set_str(zero, "0", 10);  
	mpz_init_set_str(one, "1", 10);  
	mpz_init_set_str(two, "2", 10);  
	
	mpz_sub(minusOne, n, one);

	int t = 0;
	do{
		mpz_mul(tmp, tmp, two);
		t += 1;
		mpz_fdiv_r(mid, minusOne,tmp);
	}while(mpz_cmp(mid, zero) == 0);
	t -= 1;
	mpz_fdiv_q(tmp, tmp, two);

	mpz_t u;
	mpz_init(u);
	mpz_fdiv_q(u, minusOne, tmp);

	mpz_t x0;
	mpz_t x1;
	mpz_init(x0);
	mpz_init(x1);
	exponent(x0, a, u, n);
	mpz_set(x1, x0);

	for(int i = 0;i < t;i++){
		mpz_powm_sec(x1, x0, two, n);
		if(mpz_cmp(x1, one) == 0 && mpz_cmp(x0, one) != 0 && mpz_cmp(x0, minusOne) != 0){
			return true;
		}
		mpz_set(x0, x1);
	}
	if(mpz_cmp(x1, one) != 0)
		return true;

	mpz_clear(minusOne);
	mpz_clear(zero);
	mpz_clear(one);
	mpz_clear(two);
	mpz_clear(tmp);
	mpz_clear(mid);
	mpz_clear(u);
	mpz_clear(x0);
	mpz_clear(x1);
	return false;
}

//vector<int> primes;

vector<int> initPrimes(int nums){
	bool* flag = new bool[nums + 1];
	memset(flag, 0, sizeof(bool) * (nums + 1));
	vector<int> prime;
	int cnt = 0;
	for(int i = 2;i <= nums;i++){
		if(!flag[i]){
			prime.push_back(i);
			cnt++;
		}
		for(int j = 0;j < cnt;j++){
			if(i * prime[j] > nums)
				break;
			flag[prime[j] * i] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	return prime;
}

bool millerRabin(mpz_t& n){
	LargeInt tmp;
	mpz_t b;
	vector<int> arr = initPrimes(1000);
	for(int i = 0;i < arr.size();i++){
		tmp = LargeInt(arr[i]);
		mpz_init_set_str(b, tmp.toString().c_str(), 16);
		if(witness(b, n)){
			return true;
		}
	}
	mpz_clear(b);
	return false;
}

LargeInt primeGenerate(int bits){
	LargeInt res;
	mpz_t a;
	
	res.generateRandom(bits);
	mpz_init_set_str(a, res.toString().c_str(), 16);  

	int i = 0;
	while(millerRabin(a)){
		//cout<<"*********** gene iter\t" << i++ << "\t*************"<<endl;
		res.generateRandom(bits);
		mpz_init_set_str(a, res.toString().c_str(), 16);
	}

	mpz_clear(a);
	return res;
}

