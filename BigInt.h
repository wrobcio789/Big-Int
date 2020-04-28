#pragma once
#include <climits>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <string>
#include <bitset>
#include "Tools.h"
#include "Array.h"

extern "C" uint32_t BigIntSmallDivision(uint32_t* start, int NDigits, uint32_t divider);

class BigInt
{
public:

private:
	typedef uint32_t Digit;
	typedef uint64_t DoubleDigit;
	typedef Array<Digit> DigitContainer;
	static const DoubleDigit BASE = DoubleDigit(UINT32_MAX) + 1;
	static const int PLUS = 1;
	static const int MINUS = -1;


	DigitContainer digits;
	int sign;
	

public:
	BigInt(Digit value);

	BigInt operator+(const BigInt & other) const;
	BigInt operator-(const BigInt & other) const;
	BigInt operator*(const BigInt & other) const;
	
	friend std::ostream & operator<<(std::ostream & stream, const BigInt & num);

private:
	BigInt(DigitContainer digits, int sign);
	
	static BigInt addAbs(const BigInt* a, const BigInt* b);
	static BigInt subAbs(const BigInt* a, const BigInt* b);
	static BigInt mulAbs(const BigInt* a, const BigInt* b);
	static BigInt StandardMultiplication(const BigInt* a, const BigInt* b);
	static BigInt KaratsubaMultiplication(const BigInt * a, const BigInt * b);
	static BigInt KaratsubaMultiplicationForContainers(const DigitContainer & a, const DigitContainer & b);

	BigInt & removeTrailingZeros();


	static Digit AddDigitsWithCarryAndSetCarry(Digit a, Digit b, Digit & carry);
	static Digit SubDigitsWithCarryAndSetCarry(Digit minuend, Digit substrahend, Digit & carry);
	static Digit MulDigitsWithCarryAndSetCarry(Digit a, Digit b, Digit & carry);

	static Digit AsciiToDigit(char ascii);
	static DoubleDigit ToDoubleDigit(Digit digit);
	static Digit ToDigit(DoubleDigit digit);
};

