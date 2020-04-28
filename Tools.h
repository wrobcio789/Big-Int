#pragma once
#include <cstdint>
#include <vector>

namespace Tools
{
	template<typename Iterator>
	struct scope
	{
		Iterator begin;
		Iterator end;

		scope(Iterator begin, Iterator end)
			:	begin(begin),
				end(end)
		{}

		unsigned int size()
		{
			return end - begin + 1;
		}
	};

	static uint64_t make_uint64(uint32_t larger, uint32_t smaller);
	template<typename T> static void pushValueNTimes(std::vector<T> & vec, T value, unsigned int N);
};

template<typename T>
inline void Tools::pushValueNTimes(std::vector<T>& vec, T value, unsigned int N)
{
	while (N--)
		vec.push_back(value);
}
