#include "Random.h"

RandomGen::RandomGen()
{

}

int RandomGen::GetRand(int num)
{
	static std::random_device rd;
	static std::uniform_int_distribution<int> uid(0, 1023);
	//int rand = uid(rd) % num;
	return uid(rd) % num;
}
