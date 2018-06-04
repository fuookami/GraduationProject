#pragma once

#include "_pri_math_global.h"

namespace SSUtils
{
	namespace Math
	{
		SSUtils_API_DECLSPEC std::vector<int32> nextCombination(const std::vector<int32> &currCombination, const std::vector<int32> &numbers);
		SSUtils_API_DECLSPEC std::vector<int32> prevCombination(const std::vector<int32> &currCombination, const std::vector<int32> &numbers);

		namespace Combination
		{
			SSUtils_API_DECLSPEC const bool next(std::vector<int32> &currCombination, const std::vector<int32> &numbers);
			SSUtils_API_DECLSPEC const bool prev(std::vector<int32> &currCombination, const std::vector<int32> &numbers);
		};

		struct SSUtils_API_DECLSPEC CombinationGenerator
		{
			CombinationGenerator(const std::vector<int32> _numbers);
			CombinationGenerator(const CombinationGenerator &ano) = default;
			CombinationGenerator(CombinationGenerator &&ano) = default;
			CombinationGenerator &operator=(const CombinationGenerator &ano) = default;
			CombinationGenerator &operator=(CombinationGenerator &&ano) = default;
			~CombinationGenerator(void) = default;

			const bool next(void);
			const bool prev(void);

			std::vector<int32> currCombination;
			std::vector<int32> numbers;
		};
	};
};
