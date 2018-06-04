#include "stdafx.h"
#include "Combination.h"

namespace SSUtils
{
	namespace Math
	{
		namespace Combination
		{
			const bool next(std::vector<int32>& currCombination, const std::vector<int32>& numbers)
			{
				if (currCombination.size() != numbers.size())
				{
					return false;
				}

				bool carry(false);
				++currCombination[currCombination.size() - 1];
				for (uint32 i(currCombination.size() - 1), j(-1); i != j; --i)
				{
					if (carry)
					{
						carry = false;
						++currCombination[i];
					}

					if (currCombination[i] > numbers[i])
					{
						return false;
					}
					if (currCombination[i] == numbers[i])
					{
						currCombination[i] = 0;
						carry = true;
					}
				}

				return !carry;
			}

			const bool prev(std::vector<int32>& currCombination, const std::vector<int32>& numbers)
			{
				if (currCombination.size() != numbers.size())
				{
					return false;
				}

				bool borrow(false);
				--currCombination[currCombination.size() - 1];
				for (uint32 i(currCombination.size() - 1), j(-1); i != j; --i)
				{
					if (borrow)
					{
						borrow = false;
						++currCombination[i];
					}

					if (currCombination[i] < -1)
					{
						return false;
					}
					if (currCombination[i] == -1)
					{
						currCombination[i] = numbers[i] - 1;
						borrow = true;
					}
				}

				return !borrow;
			}
		};

		std::vector<int32> nextCombination(const std::vector<int32>& currCombination, const std::vector<int32>& numbers)
		{
			std::vector<int32> temp(currCombination);
			return Combination::next(temp, numbers) ? temp : std::vector<int32>();
		}

		std::vector<int32> prevCombination(const std::vector<int32>& currCombination, const std::vector<int32>& numbers)
		{
			std::vector<int32> temp(currCombination);
			return Combination::prev(temp, numbers) ? temp : std::vector<int32>();
		}

		CombinationGenerator::CombinationGenerator(const std::vector<int32> _numbers)
			: numbers(_numbers)
		{
			currCombination.insert(currCombination.begin(), numbers.size(), 0);
		}

		const bool CombinationGenerator::next(void)
		{
			std::vector<int32> temp(currCombination);
			if (!Combination::next(temp, numbers))
			{
				return false;
			}

			currCombination = temp;
			return true;
		}

		const bool CombinationGenerator::prev(void)
		{
			std::vector<int32> temp(currCombination);
			if (!Combination::prev(temp, numbers))
			{
				return false;
			}

			currCombination = temp;
			return true;
		}
	};
};
