#include "stdafx.h"
#include "SimpleTypeAnalyzer.h"
#include "XSDToken.h"

#include <boost/algorithm/string.hpp>

#include <exception>

namespace XSDAnalyzer
{
	SimpleTypeAnalyzer::SimpleTypeAnalyzer(const std::shared_ptr<XSDFrontend::SimpleTypeModel> &simpleTypeModel)
		: m_simpleTypeModel(simpleTypeModel)
	{
	}

	std::string SimpleTypeAnalyzer::scanSimpleType(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		static const std::string EmptyString("");
		
		auto parent = node->getParent().lock();
		if (parent != nullptr && parent->getTag() == XSDFrontend::Token::SchemaTag() && !node->hasAttr(XSDFrontend::Token::NameAttr()))
		{
			std::cerr << "定义全局类型时应当有声明名字。" << std::endl;
			return EmptyString;
		}

		bool anonymous(!node->hasAttr(XSDFrontend::Token::NameAttr()));
		std::string typeName(node->hasAttr(XSDFrontend::Token::NameAttr())
			? node->getAttr(XSDFrontend::Token::NameAttr(), EmptyString)
			: m_simpleTypeModel->getNewDefaultSimpleTypeName());
		if (m_simpleTypeModel->isTypeExist(typeName))
		{
			return EmptyString;
		}

		for (const auto child : node->getChildren())
		{
			if (child != nullptr && child->getTag() == XSDFrontend::Token::RestrictionTag())
			{
				if (!analyseType(typeName, child, anonymous))
				{
					return EmptyString;
				}

				auto type(m_simpleTypeModel->getSimpleType(typeName));
				if (type != nullptr
					&& child->hasChild(XSDFrontend::Token::WhiteSpaceTag()))
				{
					const auto whiteSpaceNode(child->getChildren()[child->findChild(typeName)]);
					if (whiteSpaceNode != nullptr && whiteSpaceNode->hasAttr(XSDFrontend::Token::ValueAttr()))
					{
						type->setWhiteSpace(XSDFrontend::SimpleType::ISimpleTypeInterface::String2WhiteSpace.left.find(whiteSpaceNode->getAttr(XSDFrontend::Token::ValueAttr()))->second);
					}
				}
			}
			else if (child->getTag() == XSDFrontend::Token::ListTag())
			{
				if (!checkAndInsertType(m_simpleTypeModel->getContainerTypes(), XSDFrontend::SimpleType::ContainerType::eBaseType::tList, typeName, "", child, anonymous))
				{
					return EmptyString;
				}
				m_simpleTypeModel->checkAndEraseIlegalTypeInContainer(m_simpleTypeModel->getContainerTypes().find(typeName)->second);
			}
			else if (child->getTag() == XSDFrontend::Token::UnionTag())
			{
				if (!checkAndInsertType(m_simpleTypeModel->getContainerTypes(), XSDFrontend::SimpleType::ContainerType::eBaseType::tUnion, typeName, "", child, anonymous))
				{
					return EmptyString;
				}
				m_simpleTypeModel->checkAndEraseIlegalTypeInContainer(m_simpleTypeModel->getContainerTypes().find(typeName)->second);
			}
		}

		return typeName;
	}

	const bool SimpleTypeAnalyzer::analyseType(const std::string & typeName, const std::shared_ptr<SSUtils::XML::Node> node, const bool anonymous)
	{
		static const std::string EmptyString("");

		const std::string baseTypeName(node->getAttr(XSDFrontend::Token::BaseTypeAttr(), EmptyString));

		// 检查是否是原子类型（检查是否以xs或者xsd开头）
		if (XSDFrontend::Token::isInXSDNameSpace(baseTypeName))
		{
			/* 如果是，则在各个基础类词表中寻找类型名
			 * 如果任意一个找到了，则创建一个对应的新类型
			 * 如果没有找到，则抛出异常
			 */
			std::vector<std::string> baseTypeParts;
			boost::split(baseTypeParts, baseTypeName, boost::is_any_of(XSDFrontend::Token::NamespaceSeparator()));

			if (baseTypeParts.size() == 2)
			{
				// 查一下是不是原子类型
				if (checkAndInsertType(m_simpleTypeModel->getStringTypes(), XSDFrontend::SimpleType::StringType::String2Type, typeName, baseTypeParts.back(), node, anonymous)
					|| checkAndInsertType(m_simpleTypeModel->getNumberTypes(), XSDFrontend::SimpleType::NumberType::String2Type, typeName, baseTypeParts.back(), node, anonymous)
					|| checkAndInsertType(m_simpleTypeModel->getDatetimeTypes(), XSDFrontend::SimpleType::DatetimeType::String2Type, typeName, baseTypeParts.back(), node, anonymous)
					|| checkAndInsertType(m_simpleTypeModel->getDataTypes(), XSDFrontend::SimpleType::DataType::String2Type, typeName, baseTypeParts.back(), node, anonymous)
					)
				{
					return true;
				}
				else
				{
					static const std::string ErrorPrefix("未定义的基础类型：");
					throw std::logic_error(ErrorPrefix + baseTypeName);
				}
			}
			else
			{
				static const std::string ErrorPrefix("错误的基础类型：");
				throw std::logic_error(ErrorPrefix + baseTypeName);
			}
		}
		else
		{
			/* 如果否，检查是否已经在词表中
			 * 如果在，则衍生对应的类型，并进行增量处理
			 * 如果不在，抛出异常
			 */
			if (m_simpleTypeModel->isTypeExist(baseTypeName))
			{
				const XSDFrontend::SimpleType::ISimpleTypeInterface *prototypeSimpleType(m_simpleTypeModel->getSimpleTypes().find(baseTypeName)->second);

				switch (prototypeSimpleType->getSimpleType())
				{
				case XSDFrontend::SimpleType::eSimpleType::tStringType:
					return checkAndInsertType(m_simpleTypeModel->getStringTypes(), prototypeSimpleType, typeName, node, anonymous);
					break;
				case XSDFrontend::SimpleType::eSimpleType::tNumberType:
					return checkAndInsertType(m_simpleTypeModel->getNumberTypes(), prototypeSimpleType, typeName, node, anonymous);
					break;
				case XSDFrontend::SimpleType::eSimpleType::tDatetimeType:
					return checkAndInsertType(m_simpleTypeModel->getDatetimeTypes(), prototypeSimpleType, typeName, node, anonymous);
					break;
				case XSDFrontend::SimpleType::eSimpleType::tDataType:
					return checkAndInsertType(m_simpleTypeModel->getDataTypes(), prototypeSimpleType, typeName, node, anonymous);
				case XSDFrontend::SimpleType::eSimpleType::tContainerType:
				{
					static const std::string ErrorPrefix("该类型是容器类型（Union或List），不允许对其进行派生：");
					throw std::logic_error(ErrorPrefix + baseTypeName);
				}
				break;
				case XSDFrontend::SimpleType::eSimpleType::tNonExist:
				default:
					return false;
					break;
				}
				return false;
			}
			else
			{
				static const std::string ErrorPrefix("未定义的简单类型：");
				throw std::logic_error(ErrorPrefix + baseTypeName);
			}
		}
	}
};
