#include "BigInt.h"

BigInt::BigInt(Digit value)
	:	sign(PLUS),
		digits({value})
			
{
}

BigInt BigInt::operator+(const BigInt & other) const
{
	return addAbs(this, &other);
}

BigInt BigInt::operator-(const BigInt & other) const
{
	return subAbs(this, &other);
}

BigInt BigInt::operator*(const BigInt & other) const
{
	return mulAbs(this, &other);
}

BigInt::BigInt(DigitContainer digits, int sign)
	:	digits(digits),
		sign(sign)
{
}

BigInt BigInt::addAbs(const BigInt * a, const BigInt * b)
{
	if (a->digits.size() < b->digits.size())
		std::swap(a, b);

	DigitContainer result(a->digits.size() + 1);

	Digit carry = 0;
	for (unsigned int i = 0; i < b->digits.size(); i++)
		result[i] = AddDigitsWithCarryAndSetCarry(a->digits[i], b->digits[i], carry);
	for (unsigned int i = b->digits.size(); i < a->digits.size(); i++)
		result[i] = AddDigitsWithCarryAndSetCarry(a->digits[i], 0, carry);
	result[a->digits.size()] = carry;

	return BigInt(result, PLUS).removeTrailingZeros();
}

BigInt BigInt::subAbs(const BigInt * a, const BigInt * b)
{
	int sign = PLUS;
	unsigned int size = a->digits.size();

	if (a->digits.size() < b->digits.size())
	{
		std::swap(a, b);
		sign = MINUS;
		size = a->digits.size();
	}
	else if (a->digits.size() == b->digits.size())
	{
		int index = a->digits.size() - 1;
		while (index > 0 && a->digits[index] == b->digits[index])
			index--;
		if (a->digits[index] < b->digits[index])
		{
			std::swap(a, b);
			sign = MINUS;
		}
		
		size = index + 1;
	}

	DigitContainer result(size);

	Digit carry = 0;
	for (unsigned int i = 0; i < b->digits.size() && size; i++)
		result[i] = SubDigitsWithCarryAndSetCarry(a->digits[i], b->digits[i], carry);
	for (unsigned int i = b->digits.size(); i < size; i++)
		result[i] = SubDigitsWithCarryAndSetCarry(a->digits[i], 0, carry);

	return BigInt(result, sign).removeTrailingZeros();
}

BigInt BigInt::mulAbs(const BigInt * a, const BigInt * b)
{
	return StandardMultiplication(a, b);
}

BigInt BigInt::StandardMultiplication(const BigInt * a, const BigInt * b)
{
	DigitContainer result(a->digits.size() + b->digits.size());
	std::fill(result.begin(), result.end(), 0);

	unsigned int index = 0;
	for (Digit digit : a->digits)
	{
		Digit addingCarry = 0;
		Digit mulCarry = 0;

		unsigned int otherDigitindex = 0;
		for (Digit otherDigit : b->digits)
		{
			Digit mulDigitResult = MulDigitsWithCarryAndSetCarry(digit, otherDigit, mulCarry);
			result[index + otherDigitindex++] = AddDigitsWithCarryAndSetCarry(mulDigitResult, result[index], addingCarry);
		}

		result[index + otherDigitindex] = addingCarry + mulCarry;
		index++;
	}

	return BigInt(result, 0).removeTrailingZeros();
}

BigInt BigInt::KaratsubaMultiplication(const BigInt * a, const BigInt * b)
{
	return KaratsubaMultiplicationForContainers(a->digits, b->digits);
}

BigInt BigInt::KaratsubaMultiplicationForContainers(const DigitContainer & a, const DigitContainer & b)
{
	throw "Method not implemented";
	return BigInt(0);
}

BigInt & BigInt::removeTrailingZeros()
{
	while (digits.size() > 0 && digits.back() == 0)
		digits.shrink(1);
	return *this;
}

std::ostream & operator<<(std::ostream & stream,  const BigInt & num) 
{
	for (BigInt::Digit digit : num.digits)
		stream << digit << ' ';
	return stream;
}

BigInt::Digit BigInt::AddDigitsWithCarryAndSetCarry(Digit a, Digit b, Digit & carry)
{
	DoubleDigit result = ToDoubleDigit(a) + ToDoubleDigit(b) + ToDoubleDigit(carry);
	if (result >= BASE)
	{
		carry = 1;
		return ToDigit(result - BASE);
	}
	carry = 0;
	return ToDigit(result);
}

BigInt::Digit BigInt::SubDigitsWithCarryAndSetCarry(Digit minuend, Digit substrahend, Digit & carry)
{
	Digit totalSubstrahend = substrahend + carry;
	if (minuend < totalSubstrahend)
	{
		carry = 1;
		return minuend + ToDigit(BASE - totalSubstrahend);
	}
	carry = 0;
	return minuend - totalSubstrahend;
}

BigInt::Digit BigInt::MulDigitsWithCarryAndSetCarry(Digit a, Digit b, Digit & carry)
{
	DoubleDigit result = ToDoubleDigit(a) * ToDoubleDigit(b) + ToDoubleDigit(carry);
	carry = ToDigit(result / BASE);
	return ToDigit(result % BASE);
}

BigInt::Digit BigInt::AsciiToDigit(char ascii)
{
	return static_cast<Digit>(ascii - '0');
}

BigInt::DoubleDigit BigInt::ToDoubleDigit(Digit digit)
{
	return static_cast<DoubleDigit>(digit);
}

BigInt::Digit BigInt::ToDigit(DoubleDigit digit)
{
	return static_cast<Digit>(digit);
}