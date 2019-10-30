#ifndef _GENERATOR_H
#define _GENERATOR_H

#include "LargeInt.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <assert.h>

extern class LargeInt;

// (a ^ b) mod n
LargeInt exponent(LargeInt& a, LargeInt& b, LargeInt& n);

#endif