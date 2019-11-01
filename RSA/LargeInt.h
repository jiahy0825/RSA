#ifndef _LARGEINT_H
#define _LARGEINT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef unsigned int u32;
typedef unsigned long long ull;

#define MAX_VALUE (1 << 28) // 
// #define VAL_LEN 9
#define FORMAT_STR "%07x"

// ֧�ָ����Ӽ�
// ע�ش���public �� private

class LargeInt{
private:
	// ��������
    
	// ����������
	int symbol;

	int naiveCompare(const LargeInt &ano) const;
    int compare(const LargeInt &ano) const;
    void arrange();

    u32 estimateQuotient(const LargeInt &anoA, const LargeInt &anoB) const;
    u32 getMaxCycle(const LargeInt &anoA, const LargeInt &anoB) const;

public:
	vector<u32>  data;

    LargeInt();
    LargeInt(u32 val);
    //LargeInt(const std::string &valStr);

    // �������������
	LargeInt naivePlus(const LargeInt &one, const LargeInt &two) const;
	LargeInt naiveMinus(const LargeInt &one, const LargeInt &two) const;
    LargeInt operator+(const LargeInt &ano) const;
    LargeInt operator-(const LargeInt &ano) const;
    LargeInt operator*(const LargeInt &ano) const;
    LargeInt operator/(const LargeInt &ano) const;

	LargeInt module(const LargeInt &ano) const;
	void generateRandom(int bits);

    // �Ƚ����������
    bool operator==(const LargeInt &ano) const;
    bool operator!=(const LargeInt &ano) const;
    bool operator<(const LargeInt &ano) const;
    bool operator>(const LargeInt &ano) const;
    bool operator<=(const LargeInt &ano) const;
    bool operator>=(const LargeInt &ano) const;

    // �ַ�����ʽ�����
    string toString() const;
	string toBinString() const;
	friend ostream &operator<<(ostream &output, const LargeInt &ano);
};

#endif