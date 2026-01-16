#pragma once
#include<string_view>

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
	protected:
		std::string _Name;//反射系统会在程序结束前一直运行，构建时传入的时字面量内存一直有效可以用string_view，同时也能防止修改
		RClass* _SuperClass = nullptr;
	};
}