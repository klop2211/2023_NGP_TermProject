#pragma once

#include <random>

std::random_device rd;
std::uniform_int_distribution<> uid(0, 1023);

int getRand(int num) {
	//int rand = uid(rd) % num;
	return uid(rd) % num;
}