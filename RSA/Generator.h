#ifndef _GENERATOR_H
#define _GENERATOR_H

#include "LargeInt.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <assert.h>
#include <gmp.h>

extern class LargeInt;

// (a ^ b) mod n
LargeInt exponent2(LargeInt& a, LargeInt& b, LargeInt& n);
bool witness2(LargeInt& a, LargeInt& n);
bool millerRabin2(LargeInt& n, int bits, int s);
LargeInt primeGenerate2(int bits);

void exponent(mpz_t& res, mpz_t& a, mpz_t& b, mpz_t& n);
bool witness(mpz_t& a, mpz_t& n);
bool millerRabin(mpz_t& n, int bits, int s);
LargeInt primeGenerate(int bits);

#endif