#include "Tools.h"

uint64_t Tools::make_uint64(uint32_t larger, uint32_t smaller)
{
	uint64_t result = larger;
	result <<= 32;
	result += smaller;
	return result;
}

