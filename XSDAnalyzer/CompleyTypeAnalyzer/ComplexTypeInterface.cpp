#include "ComplexTypeInterface.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		const std::map<std::string, bool> IComplexTypeInterface::String2Abstract =
		{
			std::make_pair(SSUtils::String::True, true),
			std::make_pair(SSUtils::String::False, true)
		};

		const std::map<std::string, bool> IComplexTypeInterface::String2Mixed = 
		{
			std::make_pair(SSUtils::String::True, true),
			std::make_pair(SSUtils::String::False, false)
		};

		const std::map<std::string, IComplexTypeInterface::eBlock> IComplexTypeInterface::String2Block =
		{
			std::make_pair(std::string("extension"), IComplexTypeInterface::eBlock::tExtension),
			std::make_pair(std::string("restriction"), IComplexTypeInterface::eBlock::tRestriction),
			std::make_pair(std::string("#all"), IComplexTypeInterface::eBlock::tAll)
		};

		const std::map<std::string, IComplexTypeInterface::eFinal> IComplexTypeInterface::String2Final =
		{
			std::make_pair(std::string("extension"), IComplexTypeInterface::eFinal::tExtension),
			std::make_pair(std::string("restriction"), IComplexTypeInterface::eFinal::tRestriction),
			std::make_pair(std::string("#all"), IComplexTypeInterface::eFinal::tAll)
		};

		IComplexTypeInterface::IComplexTypeInterface(const eComplexType type)
			: IXSDNamedElementInterface(), 
			m_type(type), m_abstract(false), m_mixed(false), 
			m_block(eBlock::tNone), m_final(eFinal::tNone), 
			m_deriveType(eDerivedType::tNone), m_baseTypeName(), m_attributeGroup()
		{
		}

		IComplexTypeInterface::IComplexTypeInterface(const std::string & name, const eComplexType type)
			: IXSDNamedElementInterface(name), 
			m_type(type), m_abstract(false), m_mixed(false),
			m_block(eBlock::tNone), m_final(eFinal::tNone), 
			m_deriveType(eDerivedType::tNone), m_baseTypeName(), m_attributeGroup()
		{
		}

		IComplexTypeInterface::IComplexTypeInterface(std::string && name, const eComplexType type)
			: IXSDNamedElementInterface(std::move(name)), 
			m_type(type), m_abstract(false), m_mixed(false),
			m_block(eBlock::tNone), m_final(eFinal::tNone), 
			m_deriveType(eDerivedType::tNone), m_baseTypeName(), m_attributeGroup()
		{
		}

		std::set<std::string> IComplexTypeInterface::suppliedTokens(void) const
		{
			return std::set<std::string>();
		}

		std::set<std::string> IComplexTypeInterface::neededTokens(void) const
		{
			return std::set<std::string>();
		}
	};
};
