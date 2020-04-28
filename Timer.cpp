#include "Timer.h"



Timer::Timer(std::string name = "UNKNOWN")
{
	this->name = name;
	start = std::chrono::steady_clock::now();
}


Timer::~Timer()
{
	auto end = std::chrono::steady_clock::now();
	long long as_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Timer " << name << ". Time elapsed in microseconds " << as_microseconds << std::endl;
}
