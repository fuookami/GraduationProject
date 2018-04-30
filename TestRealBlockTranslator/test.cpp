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
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(std::numeric_limits<dec50>::digits10) << i.toDec50() << std::endl;
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
	std::string str1(_dec.toString()), str2(String::base64Decode(Data::toString(_dec.toBlock())));
	std::cout << _dec.value() << std::endl;
	std::cout << str1 << ' ' << String::isDecimal(str1) << std::endl;
	std::cout << str2 << ' ' << String::isDecimal(str2) << std::endl;
	DecimalWrapper<20> __dec(_dec.ceil<20>());
	std::cout << std::setprecision(std::numeric_limits<decimal<20>>::digits) << __dec << std::endl;
	std::cout << __dec << std::endl;
	std::cout << __dec.toString() << std::endl;

	bi = __dec.toBlock();
	DecimalWrapper<20> ___dec(bi);
	std::cout << ___dec << std::endl;
	Integer _round(___dec.roundToInteger()), _floor(___dec.floorToInteger()), _ceil(___dec.ceilToInteger());
	std::cout << _round << ' ' << _floor << ' ' << _ceil << std::endl;

	Rational r = 1;
	r /= 2;
	std::cout << r.str() << std::endl;
	bi = r.toBlock();
	Rational _r1(bi), _r2(i.toBlock(), _i.toBlock());
	std::cout << _r1 << ' ' << _r1.str() << ' ' << _r1.getNumerator() << ' ' << _r1.getDenominator() << std::endl;
	std::cout << _r2 << ' ' << _r2.str() << ' ' << _r2.getNumerator() << ' ' << _r2.getDenominator() << std::endl;
	dec50 _d(r.value_dec());
	std::cout << _d << ' ' << _r1.roundToInteger() << std::endl;

	system("pause");
	return 0;
}
