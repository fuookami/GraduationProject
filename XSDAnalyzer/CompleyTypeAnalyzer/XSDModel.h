#pragma once

#include "SimpleTypeModel.h"
#include "AttributeModel.h"
#include "ComplexTypeModel.h"

namespace XSDFrontend
{
	class XSDModel
	{
	public:
		static const std::shared_ptr<XSDModel> generateNewXSDModel(void);

	private:
		XSDModel(void);
	public:
		XSDModel(const XSDModel &ano) = delete;
		XSDModel(const XSDModel &&ano) = delete;
		XSDModel &operator=(const XSDModel &rhs) = delete;
		XSDModel &operator=(const XSDModel &&rhs) = delete;
		~XSDModel(void);

	public:
		inline const std::shared_ptr<SimpleTypeModel> getSimpleTypeModel(void) const { return m_simpleTypeModel; }
		inline const std::shared_ptr<AttributeModel> getAttributeTypeModel(void) const { return m_attributeTypeModel; }
		inline const std::shared_ptr<ComplexTypeModel> getComplexTypeModel(void) const { return m_complexTypeMode; }

		inline void clear(void) { m_simpleTypeModel->clear(); m_attributeTypeModel->clear(); m_complexTypeMode->clear(); }

	private:
		std::shared_ptr<SimpleTypeModel> m_simpleTypeModel;
		std::shared_ptr<AttributeModel> m_attributeTypeModel;
		std::shared_ptr<ComplexTypeModel> m_complexTypeMode;
	};
};
