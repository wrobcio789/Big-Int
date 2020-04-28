#pragma once
#include <string>
#include <chrono>
#include <iostream>

class Timer
{
private:
	std::string name;
	std::chrono::steady_clock::time_point start;

public:
	Timer(std::string name);
	~Timer();
};

