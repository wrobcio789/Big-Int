#include "BigInt.h"
#include <iostream>
#include <fstream>
#include "Timer.h"
#include "Array.h"

int main()
{
	BigInt x = BigInt(5643321);
	BigInt a = x * x * x;

	std::cout << a;
	return 0;
}