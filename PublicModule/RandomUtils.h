#pragma once

#include <random>

namespace SSUtils
{
	namespace Random
	{
		std::mt19937 generateNewRandomGenerator(void);
		std::mt19937_64 generateNewRandomGenerator_64(void);

		std::mt19937 &getGlobalRandomGenerator(void);
		std::mt19937_64 &getGlobalRandomGenerator_64(void);
	};
};
