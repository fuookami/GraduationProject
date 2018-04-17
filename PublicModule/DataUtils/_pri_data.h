#pragma once

#include "Global.h"
#include <memory>

namespace SSUtils
{
	namespace Data
	{
		template <typename T>
		inline const byte *getDataCBegin(const T &src)
		{
			return reinterpret_cast<const byte *>(std::addressof(src));
		}

		template <typename T>
		inline byte *getDataBegin(T &src)
		{
			return reinterpret_cast<byte *>(std::addressof(src));
		}

		template <typename T>
		inline const byte *getDataCEnd(const T &src)
		{
			static const uint8 DataLength(sizeof(T));

			return reinterpret_cast<const byte *>(std::addressof(src)) + DataLength;
		}

		template <typename T>
		inline byte *getDataEnd(T &src)
		{
			static const uint8 DataLength(sizeof(T));

			return reinterpret_cast<byte *>(std::addressof(src)) + DataLength;
		}
	};
};
