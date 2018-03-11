#pragma once

#include "SimpleTypeModel.h"
#include "XMLUtils.h"

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
		SimpleTypeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel> &simpleTypeModel);
		SimpleTypeAnalyzer(const SimpleTypeAnalyzer &ano) = delete;
		SimpleTypeAnalyzer(SimpleTypeAnalyzer &&ano) = delete;
		SimpleTypeAnalyzer &operator=(const SimpleTypeAnalyzer &rhs) = delete;
		SimpleTypeAnalyzer &operator=(SimpleTypeAnalyzer &&rhs) = delete;
		~SimpleTypeAnalyzer(void) = default;

		std::string scanSimpleType(const XMLUtils::XMLNode &node);

	private:
		const bool analyseType(const std::string &typeName, const XMLUtils::XMLNode &node);

	private:
		template<typename T>
		static const std::shared_ptr<T> getType(const std::string &typeName, const std::map<std::string, std::shared_ptr<T>> &types)
		{
			// 编译期检查模板类型是否正确
			{
				// 检查是否是基础类型
				static_assert(std::is_base_of_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T> && !std::is_same_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T>,
					"SimpleTypeAnalyzer::getType， 调用了非基础类型作为T的类型");
			}

			auto it(types.find(typeName));

			return it != types.cend() ? it->second : nullptr;
		}

		template<typename T, typename U>
		const bool checkAndInsertType(std::map<std::string, std::shared_ptr<T>> &types, const U type, const std::string &typeName, const std::string &baseTypeName, const XMLUtils::XMLNode &node)
		{
			// 编译期检查模板类型是否正确
			{
				// 基础类型与原子类型名-原子类型的映射表是否匹配
				static_assert(std::is_same_v<T::eBaseType, U>, "SimpleTypeAnalyzer::checkAndInsertType， 调用了错误的类型与原子类型名-原子类型的映射表");
			}

			std::shared_ptr<T> newType(new T(typeName, type));
			XSDFrontend::SimpleType::ISimpleTypeInterface *INewType(dynamic_cast<XSDFrontend::SimpleType::ISimpleTypeInterface *>(newType.get()));
			bool ok(INewType->refreshValidator(node));
			if (ok)
			{
				types.insert(std::make_pair(typeName, newType));
				m_simpleTypeModel->getSimpleTypes().insert(std::make_pair(typeName, INewType));
			}

			return ok;
		}

		template<typename T, typename U>
		const bool checkAndInsertType(std::map<std::string, std::shared_ptr<T>> &types, const std::map<std::string, U> &name2Type, const std::string &typeName, const std::string &baseTypeName, const XMLUtils::XMLNode &node)
		{
			// 编译期检查模板类型是否正确
			{
				// 检查是否是基础类型
				static_assert(std::is_base_of_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T> && !std::is_same_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T>,
					"SimpleTypeAnalyzer::checkAndInsertType， 调用了非基础类型作为T的类型");

				// 基础类型与原子类型名-原子类型的映射表是否匹配
				static_assert(std::is_same_v<T::eBaseType, U>, "SimpleTypeAnalyzer::checkAndInsertType， 调用了错误的类型与原子类型名-原子类型的映射表");
			}

			auto typeIt(name2Type.find(baseTypeName));
			return typeIt != name2Type.cend() && checkAndInsertType(types, typeIt->second, typeName, baseTypeName, node);
		}

		template<typename T>
		const bool checkAndInsertType(std::map<std::string, std::shared_ptr<T>> &types, const XSDFrontend::SimpleType::ISimpleTypeInterface *prototypeSimpleType, const std::string &typeName, const XMLUtils::XMLNode &node)
		{
			// 编译期检查模板类型是否正确
			{
				// 检查是否是基础类型
				static_assert(std::is_base_of_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T> && !std::is_same_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T>,
					"SimpleTypeAnalyzer::checkAndInsertType， 调用了非基础类型作为T的类型");
			}

			std::shared_ptr<T> newType(new T(typeName, (dynamic_cast<const T *>(prototypeSimpleType))->getBaseType()));
			XSDFrontend::SimpleType::ISimpleTypeInterface *INewType(dynamic_cast<XSDFrontend::SimpleType::ISimpleTypeInterface *>(newType.get()));
			INewType->setBaseTypeName(prototypeSimpleType->getName());
			bool ok(INewType->refreshValidator(node));
			if (ok)
			{
				types.insert(std::make_pair(typeName, newType));
				m_simpleTypeModel->getSimpleTypes().insert(std::make_pair(typeName, INewType));
			}

			return ok;
		}

	private:
		std::shared_ptr<XSDFrontend::SimpleTypeModel> m_simpleTypeModel;
	};
};
