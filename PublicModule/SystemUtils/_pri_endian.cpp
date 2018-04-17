#include "_pri_endian.h"

namespace SSUtils
{
	namespace System
	{
		const Endian getLocalEndian(void)
		{
			union
			{
				int number;
				char s;
			} LocalEndianChecker;

			LocalEndianChecker.number = 0x010000002;
			return (LocalEndianChecker.s == 0x01) ? Endian::BigEndian : Endian::LittleEndian;
		}
	};
};
