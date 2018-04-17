#pragma once

namespace SSUtils
{
	enum class Endian
	{
		BigEndian,
		LittleEndian
	};

	namespace System
	{
		static const unsigned int CPUIdLength = 8;

		extern const Endian LocalEndian;
	};
};
