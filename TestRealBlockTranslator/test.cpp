#include "MathUtils.h"

int main(void)
{
	using namespace SSUtils;
	using namespace SSUtils::Math;
	Integer i(Integer::generate(123));
	Block bi(i.toBlock());
	Integer _i(bi);
	Integer __i(Integer::generate(bi));
	std::cout << i.value() << ' ' << _i.value() << ' ' << __i.value() << std::endl;
	std::cout << i.toString() << ' ' << _i.toString() << ' ' << __i.toString() << std::endl;
	std::cout << std::setprecision(std::numeric_limits<dec50>::digits10) << i.toDec50() << std::endl;
	std::cout << i.toDec50().str() << std::endl;
	i += _i.value();
	std::cout << i << std::endl;
	i = bi;
	std::cout << i << std::endl;
	i += bi;
	std::cout << i << std::endl;

	Integer j(Integer::generate(124));
	std::cout << j << ' ' << (j == 124) << std::endl;
	j += 1;
	std::cout << j << ' ' << (j == 125) << std::endl;
	j += 1.2;
	std::cout << j << ' ' << (j == 126) << std::endl;

	Decimal dec(j.value());
	std::cout << dec.value() << std::endl;
	Decimal _dec(j.toDec50() / 11);
	std::cout << _dec.value() << std::endl;

	system("pause");
	return 0;
}
