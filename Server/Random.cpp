#include "Random.h"
#include <random>

float Random::GetFRandom()
{
    static std::uniform_int_distribution<> uid(0, 99);
    static std::random_device rd;


    return (float)(uid(rd)) / 100;
}
