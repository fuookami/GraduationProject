enum class Endian
{
	BigEndian,
	LittleEndian
};

template<bool is_same>
struct LocalEndianChecker
{
	static const Endian value = Endian::BigEndian;
};

template<>
struct LocalEndianChecker<true>
{
	enum { value = Endian::BigEndian };
};

template<>
struct LocalEndianChecker<false>
{
	enum { value = Endian::LittleEndian };
};

struct LocalEndian {
	static const union
	{
		int number = 0x01000002;
		char s;
	} checker;

	static const Endian value = LocalEndianChecker<checker.s == 0x01>::value;
}



int main(void)
{

}