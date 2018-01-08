#pragma once

#include "SimpleTypes.h"

#include <boost/property_tree/ptree.hpp>

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <type_traits>

namespace XSDAnalyzer
{
	class SimpleTypeAnalyzer
	{
	public:
		SimpleTypeAnalyzer(void);
		SimpleTypeAnalyzer(const SimpleTypeAnalyzer &ano) = delete;
		SimpleTypeAnalyzer(const SimpleTypeAnalyzer &&ano) = delete;
		SimpleTypeAnalyzer &operator=(const SimpleTypeAnalyzer &rhs) = delete;
		SimpleTypeAnalyzer &operator=(const SimpleTypeAnalyzer &&rhs) = delete;
		~SimpleTypeAnalyzer(void);

		const std::string scan(const boost::property_tree::ptree & pt);

		const SimpleType::eSimpleType getType(const std::string &typeName) const;
		inline const bool isTypeExist(const std::string &typeName) const { return getType(typeName) != SimpleType::eSimpleType::tNonExist; }

		const std::shared_ptr<SimpleType::StringType> getStringType(const std::string &typeName) const;
		const std::shared_ptr<SimpleType::NumberType> getNumberType(const std::string &typeName) const;
		const std::shared_ptr<SimpleType::DateTimeType> getDateTimeType(const std::string &typeName) const;
		const std::shared_ptr<SimpleType::DataType> getDataType(const std::string &typeName) const;
		const std::shared_ptr<SimpleType::ContainerType> getContainerType(const std::string &typeName) const;

	private:
		static const std::string getNewDefaultName(void);

		const bool analyseType(const std::string &typeName, const boost::property_tree::ptree &typeRoot);
		void checkAndEraseIlegalTypeInContainer(std::shared_ptr<SimpleType::ContainerType> type);

	private:
		template<typename T>
		static const std::shared_ptr<T> getType(const std::string &typeName, const std::map<std::string, std::shared_ptr<T>> &types)
		{
			// �����ڼ��ģ�������Ƿ���ȷ
			{
				// ����Ƿ��ǻ�������
				static_assert(std::is_base_of_v<SimpleType::ISimpleTypeInterface, T> && !std::is_same_v<SimpleType::ISimpleTypeInterface, T>,
					"SimpleTypeAnalyzer::checkAndInsertType�� �����˷ǻ���������ΪT������");
			}

			auto it(types.find(typeName));

			return it != types.cend() ? it->second : nullptr;
		}

		template<typename T, typename U>
		const bool checkAndInsertType(std::map<std::string, std::shared_ptr<T>> &types, const U type, const std::string &typeName, const std::string &baseTypeName, const boost::property_tree::ptree & typeRoot)
		{
			// �����ڼ��ģ�������Ƿ���ȷ
			{
				// ����������ԭ��������-ԭ�����͵�ӳ����Ƿ�ƥ��
				static_assert(std::is_same_v<T::eBaseType, U>, "SimpleTypeAnalyzer::checkAndInsertType�� �����˴����������ԭ��������-ԭ�����͵�ӳ���");
			}

			std::shared_ptr<T> newType(new T(typeName, type));
			SimpleType::ISimpleTypeInterface *INewType(dynamic_cast<SimpleType::ISimpleTypeInterface *>(newType.get()));
			INewType->refreshValidator(typeRoot);

			types.insert(std::make_pair(typeName, newType));
			m_simpleTypes.insert(std::make_pair(typeName, INewType));
			return true;
		}

		template<typename T, typename U>
		const bool checkAndInsertType(std::map<std::string, std::shared_ptr<T>> &types, const std::map<std::string, U> &name2Type, const std::string &typeName, const std::string &baseTypeName, const boost::property_tree::ptree & typeRoot)
		{
			// �����ڼ��ģ�������Ƿ���ȷ
			{
				// ����Ƿ��ǻ�������
				static_assert(std::is_base_of_v<SimpleType::ISimpleTypeInterface, T> && !std::is_same_v<SimpleType::ISimpleTypeInterface, T>, 
					"SimpleTypeAnalyzer::checkAndInsertType�� �����˷ǻ���������ΪT������");

				// ����������ԭ��������-ԭ�����͵�ӳ����Ƿ�ƥ��
				static_assert(std::is_same_v<T::eBaseType, U>, "SimpleTypeAnalyzer::checkAndInsertType�� �����˴����������ԭ��������-ԭ�����͵�ӳ���");
			}

			auto typeIt(name2Type.find(baseTypeName));
			return typeIt != name2Type.cend() && checkAndInsertType(types, typeIt->second, typeName, baseTypeName, typeRoot);
		}

		template<typename T>
		const bool checkAndInsertType(std::map<std::string, std::shared_ptr<T>> &types, const SimpleType::ISimpleTypeInterface *prototypeSimpleType, const std::string &typeName, const boost::property_tree::ptree &typeRoot)
		{
			// �����ڼ��ģ�������Ƿ���ȷ
			{
				// ����Ƿ��ǻ�������
				static_assert(std::is_base_of_v<SimpleType::ISimpleTypeInterface, T> && !std::is_same_v<SimpleType::ISimpleTypeInterface, T>, 
					"SimpleTypeAnalyzer::checkAndInsertType�� �����˷ǻ���������ΪT������");
			}

			std::shared_ptr<T> newType(new T(*dynamic_cast<const T *>(prototypeSimpleType)));
			SimpleType::ISimpleTypeInterface *INewType(dynamic_cast<SimpleType::ISimpleTypeInterface *>(newType.get()));
			INewType->setName(typeName);
			INewType->setBaseTypeName(prototypeSimpleType->getName());
			INewType->refreshValidator(typeRoot);

			types.insert(std::make_pair(typeName, newType));
			m_simpleTypes.insert(std::make_pair(typeName, INewType));

			return true;
		}

	private:
		std::map<std::string, std::shared_ptr<SimpleType::StringType>> m_stringTypes;
		std::map<std::string, std::shared_ptr<SimpleType::NumberType>> m_numberTypes;
		std::map<std::string, std::shared_ptr<SimpleType::DateTimeType>> m_dateTimeTypes;
		std::map<std::string, std::shared_ptr<SimpleType::DataType>> m_dataTypes;
		std::map<std::string, std::shared_ptr<SimpleType::ContainerType>> m_containerTypes;

		std::map<std::string, SimpleType::ISimpleTypeInterface *> m_simpleTypes;
	};
};
