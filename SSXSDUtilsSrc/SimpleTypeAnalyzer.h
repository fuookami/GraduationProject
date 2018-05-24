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
	class SSXSDUtils_API_DECLSPEC SimpleTypeAnalyzer
	{
	public:
		SimpleTypeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel> &simpleTypeModel);
		SimpleTypeAnalyzer(const SimpleTypeAnalyzer &ano) = delete;
		SimpleTypeAnalyzer(SimpleTypeAnalyzer &&ano) = delete;
		SimpleTypeAnalyzer &operator=(const SimpleTypeAnalyzer &rhs) = delete;
		SimpleTypeAnalyzer &operator=(SimpleTypeAnalyzer &&rhs) = delete;
		~SimpleTypeAnalyzer(void) = default;

		std::string scanSimpleType(const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		const bool analyseType(const std::string &typeName, const std::shared_ptr<SSUtils::XML::Node> node, const bool anonymous);

	private:
		template<typename T, typename U = std::enable_if_t<std::is_base_of_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T> && !std::is_same_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T>>>
		static const std::shared_ptr<T> getType(const std::string &typeName, const std::map<std::string, std::shared_ptr<T>> &types)
		{
			auto it(types.find(typeName));
			return it != types.cend() ? it->second : nullptr;
		}

		template<typename T, typename U>
		typename std::enable_if_t<std::is_same_v<typename T::eBaseType, U>, const bool> checkAndInsertType(std::map<std::string, std::shared_ptr<T>> &types, const U type, const std::string &typeName, const std::string &baseTypeName, const std::shared_ptr<SSUtils::XML::Node> node, const bool anonymous)
		{
			std::shared_ptr<T> newType(new T(typeName, type));
			XSDFrontend::SimpleType::ISimpleTypeInterface *INewType(dynamic_cast<XSDFrontend::SimpleType::ISimpleTypeInterface *>(newType.get()));
			bool ok(INewType->refreshValidator(node));
			INewType->setAnonymous(anonymous);
			INewType->loadExAttr(node->getParent().lock(), XSDFrontend::SimpleType::ISimpleTypeInterface::BaseAttrs);
			if (ok)
			{
				types.insert(std::make_pair(typeName, newType));
			}

			return ok;
		}

		template<typename T, typename U>
		typename std::enable_if_t<std::is_base_of_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T> && !std::is_same_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T> && std::is_same_v<typename T::eBaseType, U>, const bool> checkAndInsertType(std::map<std::string, std::shared_ptr<T>> &types, const boost::bimap<std::string, U> &name2Type, const std::string &typeName, const std::string &baseTypeName, const std::shared_ptr<SSUtils::XML::Node> node, const bool anonymous)
		{
			auto typeIt(name2Type.left.find(baseTypeName));
			return typeIt != name2Type.left.end() && checkAndInsertType(types, typeIt->second, typeName, baseTypeName, node, anonymous);
		}

		template<typename T>
		typename std::enable_if_t<std::is_base_of_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T> && !std::is_same_v<XSDFrontend::SimpleType::ISimpleTypeInterface, T>, const bool> checkAndInsertType(std::map<std::string, std::shared_ptr<T>> &types, const XSDFrontend::SimpleType::ISimpleTypeInterface *prototypeSimpleType, const std::string &typeName, const std::shared_ptr<SSUtils::XML::Node> node, const bool anonymous)
		{
			std::shared_ptr<T> newType(new T(typeName, (dynamic_cast<const T *>(prototypeSimpleType))->getBaseType()));
			XSDFrontend::SimpleType::ISimpleTypeInterface *INewType(dynamic_cast<XSDFrontend::SimpleType::ISimpleTypeInterface *>(newType.get()));
			INewType->setBaseTypeName(prototypeSimpleType->getName());
			INewType->setAnonymous(anonymous);
			INewType->loadExAttr(node->getParent().lock(), XSDFrontend::SimpleType::ISimpleTypeInterface::BaseAttrs);
			bool ok(INewType->refreshValidator(node));
			if (ok)
			{
				types.insert(std::make_pair(typeName, newType));
			}

			return ok;
		}

	private:
		std::shared_ptr<XSDFrontend::SimpleTypeModel> m_simpleTypeModel;
	};
};
