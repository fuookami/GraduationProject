#include "XSDModel.h"

namespace XSDFrontend
{
	const std::shared_ptr<XSDModel> XSDModel::generateNewXSDModel(void)
	{
		return std::shared_ptr<XSDModel>(new XSDModel());
	}

	XSDModel::XSDModel(void)
		: m_simpleTypeModel(new SimpleTypeModel()), m_attributeTypeModel(new AttributeModel()), m_complexTypeMode(new ComplexTypeModel())
	{
	}

	XSDModel::~XSDModel(void)
	{
	}
};
