#ifndef _LARGEINT_H
#define _LARGEINT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef unsigned int u32;
typedef unsigned long long ull;

#define MAX_VALUE (1 << 28) // 
#define VAL_LEN 7
#define FORMAT_STR "%07x"

// 支持负数加减
// 注重代码public 和 private

class LargeInt{
private:
	// 保存数据
	vector<u32>  data;
	// 保存正负号
	int symbol;

	int naiveCompare(const LargeInt &ano) const;
    int compare(const LargeInt &ano) const;
    void arrange();

    u32 estimateQuotient(const LargeInt &anoA, const LargeInt &anoB) const;
    u32 getMaxCycle(const LargeInt &anoA, const LargeInt &anoB) const;

public:
    LargeInt();
    LargeInt(u32 val);
    //LargeInt(const std::string &valStr);

    // 四则运算符重载
	LargeInt naivePlus(const LargeInt &one, const LargeInt &two) const;
	LargeInt naiveMinus(const LargeInt &one, const LargeInt &two) const;
    LargeInt operator+(const LargeInt &ano) const;
    LargeInt operator-(const LargeInt &ano) const;
    LargeInt operator*(const LargeInt &ano) const;
    LargeInt operator/(const LargeInt &ano) const;

	LargeInt module(const LargeInt &ano) const;
	void generateRandom(int bits);

    // 比较运算符重载
    bool operator==(const LargeInt &ano) const;
    bool operator!=(const LargeInt &ano) const;
    bool operator<(const LargeInt &ano) const;
    bool operator>(const LargeInt &ano) const;
    bool operator<=(const LargeInt &ano) const;
    bool operator>=(const LargeInt &ano) const;

    // 字符串格式化输出
    string toString() const;
	string toBinString() const;
	friend ostream &operator<<(ostream &output, const LargeInt &ano);
	void transform(string& str);
};

#endif