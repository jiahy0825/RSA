#include "stdafx.h"

#include "LargeInt.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstring>
#include <random>
#include <string.h>
#include <assert.h>
#include <gmp.h>


using namespace std;

#ifndef MIN
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

inline bool isDigit(const char ch){
    return ch >= '0' && ch <= '9';
}

LargeInt::LargeInt() {
	this->symbol = 1;
	//this->data.push_back(0);
}

LargeInt::LargeInt(u32 val){
	this->data.push_back(val % MAX_VALUE);
	this->symbol = 1;
    if (val >= MAX_VALUE)
        this->data.push_back(val / MAX_VALUE);
}

// ȥ������������������еĸ�λ���ڶ������
void LargeInt::arrange(){
    int idx = this->data.size();

    // ע�⣬���������ȫΪ0��Ҫ�������λ��0
    while (--idx >= 1){
        if (this->data[idx] > 0) 
			break;
        this->data.pop_back();
    }
	
	// ������Ϊ0ʱ����֤����Ϊ��
	if(this->data.size() == 1 && this->data[0] == 0){
		this->symbol = 1;
	}
}

// �ȽϺ�����0 ��ȣ�1 ���ڣ�-1 С��
int LargeInt::compare(const LargeInt &ano) const{
	if(this->symbol != ano.symbol){
		return this->symbol == 1 ? 1 : -1;
	}
	
	int len1 = this->data.size();
    int len2 = ano.data.size();

    // step1: �Ƚϳ���
    if (len1 != len2)
        return (len1 > len2) ? this->symbol : (-1 * this->symbol);

    // step2: �ɸ�λ����λ�Ƚ�ֵ
    for (int idx = len1 - 1; idx >= 0; --idx){
        if (this->data[idx] == ano.data[idx]) 
			continue;
        return this->data[idx] > ano.data[idx] ? this->symbol : (-1 * this->symbol);
    }

    return 0;
}

int LargeInt::naiveCompare(const LargeInt &ano) const{
	int len1 = this->data.size();
    int len2 = ano.data.size();

    // step1: �Ƚϳ���
    if (len1 != len2)
        return (len1 > len2) ? 1 : -1;

    // step2: �ɸ�λ����λ�Ƚ�ֵ
    for (int idx = len1 - 1; idx >= 0; --idx){
        if (this->data[idx] == ano.data[idx]) 
			continue;
        return this->data[idx] > ano.data[idx] ? 1 : -1;
    }

    return 0;
}

bool LargeInt::operator==(const LargeInt &ano) const{
    return compare(ano) == 0;
}

bool LargeInt::operator!=(const LargeInt &ano) const{
    return compare(ano) != 0;
}

bool LargeInt::operator<(const LargeInt &ano) const{
    return compare(ano) < 0;
}

bool LargeInt::operator>(const LargeInt &ano) const{
    return compare(ano) > 0;
}

bool LargeInt::operator<=(const LargeInt &ano) const{
    return compare(ano) <= 0;
}

bool LargeInt::operator>=(const LargeInt &ano) const{
    return compare(ano) >= 0;
}

LargeInt LargeInt::naivePlus(const LargeInt &one, const LargeInt &two) const{
	LargeInt res;
	int len1 = one.data.size();
	int len2 = two.data.size();

	u32 add = 0;
	u32 val = 0;
	int i = 0;
	while(i < len1 && i < len2){
		val = one.data[i] + two.data[i] + add;
		if (val >= MAX_VALUE){
			res.data.push_back(val - MAX_VALUE);
			add = 1;
		}else{
			res.data.push_back(val);
			add = 0;
		}
		i++;
	}
	while(i < len1){
		val = one.data[i] + add;
		if (val >= MAX_VALUE){
			res.data.push_back(val - MAX_VALUE);
			add = 1;
		}else{
			res.data.push_back(val);
			add = 0;
		}
		i++;
	}
	while (i < len2){
		val = two.data[i] + add;
		if (val >= MAX_VALUE){
			res.data.push_back(val - MAX_VALUE);
			add = 1;
		}else{
			res.data.push_back(val);
			add = 0;
		}
		i++;
	}
	if(add){
		res.data.push_back(add);
	}
	return res;
}

LargeInt LargeInt::naiveMinus(const LargeInt &one, const LargeInt &two) const{
	assert(one.naiveCompare(two) >= 0);

	int len1 = one.data.size();
	int len2 = two.data.size();

	u32 val = 0;
	u32 minu = 0;
	LargeInt res;

	for(int i = 0;i < len2;i++){
		if(one.data[i] < two.data[i] + minu){
			val = one.data[i] + MAX_VALUE - minu - two.data[i];
			minu = 1;
		}else{
			val = one.data[i] - minu - two.data[i];
			minu = 0;
		}
		res.data.push_back(val);
	}

	for(int i = len2;i < len1;i++){
		if(one.data[i] < minu){
			val = one.data[i] + MAX_VALUE - minu;
			minu = 1;
		}else{
			val = one.data[i] - minu;
			minu = 0;
		}
		res.data.push_back(val);
	}
	res.arrange();
	return res;
}

LargeInt LargeInt::operator+(const LargeInt &ano) const
{
	LargeInt res;
	if(this->symbol == ano.symbol){
		res = naivePlus(*this, ano);
		res.symbol = this->symbol;
		res.arrange();
		return res;
	}
	int sym = this->symbol;
	int comp = naiveCompare(ano);
	if(comp == 0){
		res = LargeInt(0);
		res.symbol = 1;
	}else if (comp == 1){
		res = naiveMinus(*this, ano);
		res.symbol = sym;
	}else{
		res = naiveMinus(ano, *this);
		res.symbol = -sym;
	}
	res.arrange();
	return res;
}

LargeInt LargeInt::operator-(const LargeInt &ano) const
{
    LargeInt res;
	if(this->symbol != ano.symbol){
		res = naivePlus(*this, ano);
		res.symbol = this->symbol;
		return res;
	}
	int sym = this->symbol;
	int comp = naiveCompare(ano);
	if(comp == 0){
		res = LargeInt(0);
		res.symbol = 1;
	}else if (comp == 1){
		res = naiveMinus(*this, ano);
		res.symbol = sym;
	}else{
		res = naiveMinus(ano, *this);
		res.symbol = -sym;
	}
	res.arrange();
	return res;
}

LargeInt LargeInt::operator*(const LargeInt &ano) const
{
    int len1 = this->data.size();
    int len2 = ano.data.size();

	// ��֤������λ�����ڳ���
    if (len1 < len2) return ano.operator*(*this); 

	// ��
    ull value;
	// ��λ
    ull mult = 0;
    LargeInt res;
    LargeInt tmp;

    for (int idx2 = 0; idx2 < len2; idx2++)
    {
        tmp.data.clear();
		tmp.symbol = 1;
        mult = 0;

        // ����
        for (int i = 0;i < idx2; i++)
            tmp.data.push_back(0);
        for (int idx1 = 0; idx1 < len1; idx1++){
            value = (ull)(ano.data[idx2]) * (ull)(this->data[idx1]) + mult;
            tmp.data.push_back((u32)(value % MAX_VALUE));
            mult = value / MAX_VALUE;
        }
        if (mult)
            tmp.data.push_back((u32)mult);

        res = res + tmp;
    }
	res.symbol = this->symbol * ano.symbol;
    return res;
}

/*----------------------------------*/
/*	  �Զ����������-���Ӷȹ���	    */
/*----------------------------------*/

//LargeInt LargeInt::operator/(const LargeInt &ano) const{
//	if (ano.data.empty() || ano == LargeInt(0)){
//		cout << "��������!!!" <<endl;
//		return LargeInt();
//	}
//	if (naiveCompare(ano) == -1){
//		return LargeInt(0);
//	}
//
//    int len1 = this->data.size();
//    int len2 = ano.data.size();
//
//    u32 value;
//    LargeInt res;
//    LargeInt tmp;
//	LargeInt cal;
//
//    for (int idx = len1 - len2 + 1; idx < len1; idx++){
//        tmp.data.push_back(this->data[idx]);
//    }
//
//    // len1 >= len2
//    for (int idx = len1 - len2; idx >= 0; idx--){
//        tmp.data.insert(tmp.data.begin(), this->data[idx]);
//        tmp.arrange();
//
//        value = getMaxCycle(tmp, ano); // ��
//
//		cal = ano * value;
//		if(tmp.naiveCompare(cal) >= 0)
//	        tmp = naiveMinus(tmp, cal);   // ����
//
//        res.data.insert(res.data.begin(), value); // �������ɸ�λ���λ���У����Բ���λ����begin
//    }
//
//    res.arrange();
//	res.symbol = this->symbol * ano.symbol;
//    return res;
//}

LargeInt LargeInt::operator/(const LargeInt &ano) const{
	if (ano.data.empty() || ano == LargeInt(0)){
		cout << "��������!!!" <<endl;
		return LargeInt();
	}
	if (naiveCompare(ano) == -1){
		return LargeInt(0);
	}

	mpz_t a, b, c;
	mpz_init(a);
	mpz_init_set_str(b, this->toString().c_str(), 16);  
	mpz_init_set_str(c, ano.toString().c_str(), 16); 
	mpz_fdiv_q(a, b, c);
	char* buff = new char[3000];
	gmp_sprintf(buff, "%Zx", a);
	string str(buff);
	LargeInt res;
	res.transform(str);
	

	//cout<<str<<endl;
	//cout<<res<<endl;

	delete[] buff;
    return res;
}

LargeInt LargeInt::module(const LargeInt &ano) const{
	mpz_t a, b, c;
	mpz_init(a);
	mpz_init_set_str(b, this->toString().c_str(), 16);
	mpz_init_set_str(c, ano.toString().c_str(), 16);
	mpz_fdiv_r(a, b, c);
	char* buff = new char[3000];
	gmp_sprintf(buff, "%Zx", a);
	string str(buff);
	LargeInt res;
	res.transform(str);

	delete[] buff;
	return res;

	//LargeInt quotient = *this / ano;
	//return *this - quotient * ano;
}

// ������ֵ
u32 LargeInt::getMaxCycle(const LargeInt &A, const LargeInt &B) const{
    LargeInt tmpA = A;
    const LargeInt& tmpB = B;
	LargeInt cal;
    u32 quotient;
    u32 res = 0;
    bool flag = true;

    while(tmpA.naiveCompare(tmpB) >= 0){
        quotient = estimateQuotient(tmpA, tmpB);

		cal = tmpB * quotient;

		if(cal.naiveCompare(tmpA) >= 0)
	        tmpA = naiveMinus(cal, tmpA);
		else
			tmpA = 0;

        res = flag ? (res + quotient) : (res - quotient);
        flag = !flag;
    }

    // ΢�� 
    while (res > 0 && (B * res) > A) {
		res--;
	}

    return res;
}

// ��ֵ
u32 LargeInt::estimateQuotient(const LargeInt &A, const LargeInt &B) const{
    int lenA = A.data.size();
    int lenB = B.data.size();
    ull valA, valB;

    if (lenA == lenB){
        if (lenA > 1){
            valA = (ull)A.data[lenA - 1] * MAX_VALUE + A.data[lenA - 2];
            valB = (ull)B.data[lenB - 1] * MAX_VALUE + B.data[lenB - 2];
        }
        else{
            valA = (ull)A.data[lenA - 1];
            valB = (ull)B.data[lenB - 1];
        }
    }else{
        valA = (ull)A.data[lenA - 1] * MAX_VALUE + A.data[lenA - 2];
        valB = (ull)B.data[lenB - 1];
    }

    return (u32)(valA / valB);
}


//LargeInt LargeInt::module(const LargeInt &ano) const{
//	LargeInt quotient = *this / ano;
//	return *this - quotient * ano;
//
//	//cout<<"***********"<<endl;
//	//cout<<ano<<endl;
//	//cout<<quotient<<endl;
//	//cout<<ano * quotient<<endl;
//	//cout<<*this<<endl;
//	//cout<<"***********"<<endl;
//
//	//return (*this).naiveMinus(*this, quotient * ano);
//}

//LargeInt LargeInt::module(const LargeInt &ano) const{
//	if (ano.data.empty() || ano == LargeInt(0)){
//		cout << "ģ������!!!" <<endl;
//		return LargeInt();
//	}
//
//	int comRes = this->naiveCompare(ano);
//	if(comRes < 0){
//		return *this;
//	}else if(comRes == 0){
//		return LargeInt(0);
//	}
//
//    int len1 = this->data.size();
//    int len2 = ano.data.size();
//
//	//cout<<"len1\t"<<len1<<"\tlen2\t"<<len2<<endl;
//
//    u32 value;
//    LargeInt tmp;
//	LargeInt cal;
//	//cout<<"module init"<<endl;
//    for (int idx = len1 - len2 + 1; idx < len1; idx++){
//        tmp.data.push_back(this->data[idx]);
//    }
//	//cout<<"module mid"<<endl;
//    // len1 >= len2
//    for (int idx = len1 - len2; idx >= 0; idx--){
//        tmp.data.insert(tmp.data.begin(), this->data[idx]);
//        tmp.arrange();
//
//        value = getMaxCycle(tmp, ano); // ��
//
//		cal = ano * value;
//		if(tmp.naiveCompare(cal) >= 0)
//	        tmp = naiveMinus(tmp, cal);   // ����
//		//cout<<"idx"<<idx<<endl;
//    }
//	tmp.arrange();
//	//cout<<"module finish"<<endl;
//    return tmp;
//}

int get_random(int bits){
	u32 res = 0;
	if(bits == 28){
		res = (u32)((rand() * 1.0 / RAND_MAX) * MAX_VALUE);
	}else{
		res = (u32)((rand() * 1.0 / RAND_MAX) * pow(2, bits));
	}
	if(res == 0)
		res += 1;
	return res;
}

void LargeInt::generateRandom(int bits){
	this->data = vector<u32>((bits + 27) / 28, 0);
	int index = 0;
	u32 ran = 0;
	while(bits > 28){
		ran = get_random(28);
		if(index == 0 && ran % 2 == 0){
			ran -= 1;
		}
		this->data[index++] = ran;
		bits -= 28;
	}
	if(bits != 0){
		ran = get_random(bits);
		if(index == 0 && ran % 2 == 0){
			ran -= 1;
		}
		this->data[index++] = ran;
	}
	this->arrange();
}

string LargeInt::toString() const{
    int len = this->data.size();
    int shift = 0;
	// +2��Ϊ����������λ�������ڴ�й©
    char *buff = new char[len * 7 + 2];

	if (this->symbol == -1){
		shift += sprintf(buff + shift, "-");
	}

    if (len > 0)
        shift += sprintf(buff + shift, "%x", this->data[len - 1]);

    for (int idx = len - 2; idx >= 0; idx--)
    {
        shift += sprintf(buff + shift, FORMAT_STR, this->data[idx]);
    }
    buff[shift] = '\0';

    string retStr(buff);
    delete[] buff;

    return retStr;
}

string LargeInt::toBinString() const{
	int len = this->data.size();
	string res;
	string tmp;
	u32 num = 0;
	for(int i = len - 1;i >= 0;i--){
		num = this->data[i];
		tmp.clear();
		while(num > 0){
			tmp += (char)('0' + (num & 0x1));
			num >>= 1;
		}
		reverse(tmp.begin(), tmp.end());
		assert(tmp.length() >= 0 && tmp.length() <= 28);
		tmp = string(28 - tmp.length(), '0') + tmp;
		res += tmp;
	}
	return res;
}

ostream &operator<<(ostream &output, const LargeInt &ano){
	output << ano.toString();
	return output; 
}

void LargeInt::transform(string& str){
	int len = str.length();
	string s;
	if(str[0] == '-'){
		this->symbol = -1;
		str = str.substr(1);
		len -= 1;
	}
	while(len >= VAL_LEN){
		s = str.substr(len - VAL_LEN, VAL_LEN);
		this->data.push_back(strtol(s.c_str(), NULL, 16));
		len -= VAL_LEN;
	}
	if(len > 0){
		s = str.substr(0, len);
		this->data.push_back(strtol(s.c_str(), NULL, 16));
	}
	this->arrange(); // ȥ��
}