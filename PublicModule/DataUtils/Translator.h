#pragma once

#include "_pri_data.h"
#include "SystemUtils.h"
#include <array>
#include <algorithm>

namespace SSUtils
{
	namespace Data
	{
		template <typename T>
		struct Translator
		{
			static const uint8 DataLength = sizeof(T);
			Endian endian;

			Translator(const Endian _endian = System::LocalEndian)
				: endian(_endian) {}
			Translator(const Translator &ano) = delete;
			Translator(Translator &&ano) = delete;
			Translator &operator=(const Translator &rhs) = delete;
			Translator &operator=(Translator &&rhs) = delete;
			~Translator(void) = default;

			Block fromData(const T &src)
			{
				Block buff(DataLength, 0);
				if (DataLength == 1 || endian == Endian::BigEndian)
				{
					std::copy(getDataCBegin(src), getDataCEnd(src), buff.begin());
				}
				else
				{
					std::copy(getDataCBegin(src), getDataCEnd(src), buff.begin());
					std::reverse(buff.begin(), buff.end());
				}

				return buff;
			}

			template <typename container>
			Block fromDataContainer(const container &datas)
			{
				static_assert(std::is_same_v<container::value_type, T>, "SSUtils::Translotor::fromDataContainer, the value type of container is not the same of the type");
				Block buff;
				if (DataLength == 1 || endian == Endian::BigEndian)
				{
					for (const auto &data : datas)
					{
						std::copy(getDataCBegin(data), getDataCEnd(data), std::back_inserter(buff));
					}
				}
				else
				{
					for (const auto &data : datas)
					{
						std::copy(getDataCBegin(data), getDataCEnd(data), std::back_inserter(buff));
						std::reverse(buff.end() - DataLength, buff.end());
					}
				}

				return buff;
			}

			template <typename iter>
			Block fromDataIterator(const iter bgIt, const iter edIt)
			{
				static_assert(std::is_same_v<iter::value_type, T>, "SSUtils::Translotor::fromDataIterator, the value type of iterator is not the same of the type");
				Block buff;
				if (DataLength == 1 || endian == Endian::BigEndian)
				{
					for (iter curr; curr != edIt; ++curr)
					{
						T &data(*curr);
						std::copy(getDataCBegin(data), getDataCEnd(data), std::back_inserter(buff));
					}
				}
				else
				{
					for (iter curr; curr != edIt; ++curr)
					{
						T &data(*curr);
						std::copy(getDataCBegin(data), getDataCEnd(data), std::back_inserter(buff));
						std::reverse(buff.end() - DataLength, buff.end());
					}
				}


				return buff;
			}

			T toData(const Block &data)
			{
				if (data.size() != DataLength)
				{
					return T();
				}
				else
				{
					T ret;
					if (DataLength == 1 || endian == Endian::BigEndian)
					{
						std::copy(data.cbegin(), data.cend(), getDataBegin(ret));
					}
					else
					{
						std::copy(data.crbegin(), data.crend(), getDataBegin(ret));
					}

					return ret;
				}
			}

			template<uint32 size>
			std::array<T, size> toDataArray(const Block &datas)
			{
				if (data.size() != (size * DataLength))
				{
					return std::array<T, size>();
				}
				else
				{
					std::array<T, size> ret;
					if (DataLength == 1 || endian == Endian::BigEndian)
					{
						for (uint32 i(0), j(datas.size()); i != j; i += DataLength)
						{
							std::copy(datas.cbegin() + i, datas.cbegin() + i + DataLength, getDataBegin(ret[i / DataLength]));
						}
					}
					else
					{
						for (uint32 i(0), j(datas.size()); i != j; i += DataLength)
						{
							Block data(DataLength, 0);
							std::reverse_copy(datas.cbegin() + i, datas.cbegin() + i + DataLength, data.begin());
							std::copy(data.cbegin(), data.cend(), getDataBegin(ret[i / DataLength]));
						}
					}

					return ret;
				}
			}

			template<typename container>
			container toDataContainer(const Block &datas)
			{
				static_assert(std::is_same_v<container::value_type, T>, "SSUtils::Translotor::toDataContainer, the value type of container is not the same of the type");
				if (data.size() % DataLength != 0)
				{
					return std::vector<T>();
				}
				else
				{
					container ret;
					if (DataLength == 1 || endian == Endian::BigEndian)
					{
						for (uint32 i(0), j(datas.size()); i != j; i += DataLength)
						{
							T temp;
							std::copy(datas.cbegin() + i, datas.cbegin() + i + DataLength, getDataBegin(temp));

							ret.insert(ret.end(), std::move(temp));
						}
					}
					else
					{
						for (uint32 i(0), j(datas.size()); i != j; i += DataLength)
						{
							T temp;
							Block data(DataLength, 0);
							std::reverse_copy(datas.cbegin() + i, datas.cbegin() + i + DataLength, data.begin());
							std::copy(data.cbegin(), data.end(), getDataBegin(temp));

							ret.insert(ret.end(), std::move(temp));
						}
					}

					return ret;
				}
			}

			template<typename outIt>
			outIt toDataIterator(const Block &data, outIt it)
			{
				static_assert(std::is_same_v<outIt::value_type, T>, "SSUtils::Translotor::toDataIterator, the value type of iterator is not the same of the type");
				if (data.size() % DataLength != 0)
				{
					return std::vector<T>();
				}
				else
				{
					if (DataLength == 1 || endian == Endian::BigEndian)
					{
						for (uint32 i(0), j(datas.size()); i != j; i += DataLength)
						{
							T temp;
							std::copy(datas.cbegin() + i, datas.cbegin() + i + DataLength, getDataBegin(temp));

							it = std::move(temp);
							++it;
						}
					}
					else
					{
						for (uint32 i(0), j(datas.size()); i != j; i += DataLength)
						{
							T temp;
							Block data(DataLength, 0);
							std::reverse_copy(datas.cbegin() + i, datas.cbegin() + i + DataLength, data.begin());
							std::copy(data.cbegin(), data.end(), getDataBegin(temp));

							it = std::move(temp);
							++it;
						}
					}

					return it;
				}
			}
		};

		inline const bool toBool(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<bool> translator(endian);
			return translator.toData(data);
		}
		inline Block fromBool(const bool value, const Endian endian = System::LocalEndian)
		{
			static Translator<bool> translator(endian);
			return translator.fromData(value);
		}

		inline const float toFloat(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<float> translator(endian);
			return translator.toData(data);
		}
		inline Block fromFloat(const float value, const Endian endian = System::LocalEndian)
		{
			static Translator<float> translator(endian);
			return translator.fromData(value);
		}

		inline const double toDouble(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<double> translator(endian);
			return translator.toData(data);
		}
		inline Block fromDouble(const double value, const Endian endian = System::LocalEndian)
		{
			static Translator<double> translator(endian);
			return translator.fromData(value);
		}

		inline const int8 toInt8(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<int8> translator(endian);
			return translator.toData(data);
		}
		inline Block fromInt8(const int8 value, const Endian endian = System::LocalEndian)
		{
			static Translator<int8> translator(endian);
			return translator.fromData(value);
		}
		inline const uint8 toUInt8(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<uint8> translator(endian);
			return translator.toData(data);
		}
		inline Block fromUInt8(const uint8 value, const Endian endian = System::LocalEndian)
		{
			static Translator<uint8> translator(endian);
			return translator.fromData(value);
		}

		inline const int16 toInt16(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<int16> translator(endian);
			return translator.toData(data);
		}
		inline Block fromInt16(const int16 value, const Endian endian = System::LocalEndian)
		{
			static Translator<int16> translator(endian);
			return translator.fromData(value);
		}
		inline const uint16 toUInt16(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<uint16> translator(endian);
			return translator.toData(data);
		}
		inline Block fromUInt16(const uint16 value, const Endian endian = System::LocalEndian)
		{
			static Translator<uint16> translator(endian);
			return translator.fromData(value);
		}

		inline const int32 toInt32(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<int32> translator(endian);
			return translator.toData(data);
		}
		inline Block fromInt32(const int32 value, const Endian endian = System::LocalEndian)
		{
			static Translator<int32> translator(endian);
			return translator.fromData(value);
		}
		inline const uint32 toUInt32(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<uint32> translator(endian);
			return translator.toData(data);
		}
		inline Block fromUInt32(const uint32 value, const Endian endian = System::LocalEndian)
		{
			static Translator<uint32> translator(endian);
			return translator.fromData(value);
		}
		
		inline const int64 toInt64(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<int64> translator(endian);
			return translator.toData(data);
		}
		inline Block fromInt64(const int64 value, const Endian endian = System::LocalEndian)
		{
			static Translator<int64> translator(endian);
			return translator.fromData(value);
		}
		inline const uint64 toUInt64(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<uint64> translator(endian);
			return translator.toData(data);
		}
		inline Block fromUInt64(const uint64 value, const Endian endian = System::LocalEndian)
		{
			static Translator<uint64> translator(endian);
			return translator.fromData(value);
		}

		template<typename T>
		inline Block fromData(const T &data, const Endian endian = System::LocalEndian)
		{
			static Translator<T> translator(endian);
			return translator.fromData(data);
		}
		template<typename T>
		inline T toData(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<T> translator(endian);
			return translator.toData(data);
		}

		template<typename T, uint32 size>
		inline Block fromArray(const std::array<T, size> &datas, const Endian endian = System::LocalEndian)
		{
			static Translator<T> translator(endian);
			return translator.fromDataContainer(datas);
		}
		template<typename T, uint32 size>
		inline std::array<T, size> toArray(const Block &datas, const Endian endian = System::LocalEndian)
		{
			static Translator<T> translator(endian);
			return translator.toDataArray<size>(datas);
		}

		template<typename container>
		inline Block fromContainer(const container &datas, const Endian endian = System::LocalEndian)
		{
			static Translator<T> translator(endian);
			return translator.fromDataContainer(datas);
		}
		template<typename container>
		inline container toContainer(const Block &data, const Endian endian = System::LocalEndian)
		{
			static Translator<T> translaotr(endian);
			return translaotr.toDataContainer<container>(data);
		}

		template<typename iter>
		inline Block fromIterator(const iter bgIt, const iter edIt, const Endian endian = System::LocalEndian)
		{
			static Translator<T> translator(endian);
			return translator.fromDataIterator(bgIt, edIt);
		}
		template<typename outIt>
		inline outIt toIterator(const Block &data, outIt it, const Endian endian = System::LocalEndian)
		{
			static Translator<T> translator(endian);
			return translator.toDataIterator(data, it);
		}
	};
};
