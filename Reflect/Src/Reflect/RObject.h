#pragma once
#include<string>
namespace reflect
{
	class RClass;
	class RObject
	{
		friend class RObjectSetter;
	public:
		RObject()=default;
		virtual ~RObject()=default;
		const RClass* SuperClass()const { return _SuperClass; }
		std::string GetName()const { return std::string(_Name); }
		size_t GetHashCode()const { return _HashCode; }
	protected:
		std::string _Name="";
		RClass* _SuperClass = nullptr;
		size_t _HashCode;
	};
}