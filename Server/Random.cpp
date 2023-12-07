#include "Random.h"
#include <random>

float Random::GetFRandom()
{
    static std::uniform_int_distribution<> uid(0, 99);
    static std::random_device rd;


    return (float)(uid(rd)) / 100;
}

int Random::GetRand(int num)
{
	static std::random_device rd;
	static std::uniform_int_distribution<int> uid(0, 999);

	//int rand = uid(rd) % num;
	return uid(rd) % num;
}
