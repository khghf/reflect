#include"RawTypeDescriptorBuilder.h"
#include"ReflectInfoRegistry .h"
namespace reflect
{

	RawTypeDescriptorBuilder::RawTypeDescriptorBuilder(const std::string& name):
		m_Desc(std::make_unique<TypeDescriptor>())
	{
		m_Desc->m_Name = name;
	}

	

	RawTypeDescriptorBuilder::~RawTypeDescriptorBuilder()
	{
		ReflectInfoRegistry::Instance().Register(std::move(m_Desc));
	}

}