#pragma once
#include"RObject.h"
namespace reflect
{
	class RClass;
	class RProperty :public RObject
	{
		friend class RObjectSetter;
	public:
		template<typename Class,typename Var>
		RProperty(Var Class::* var)
		{
			_Offset = (size_t)(&(static_cast<Class*>(nullptr)->*var));
		}
		template<typename Class, typename VarType>
		VarType GetValue(Class& obj)const { return *(VarType*)((size_t)&obj + _Offset); }
		template<typename VarType,typename Class>
		void SetValue(Class& obj, const VarType& Val) { (*(VarType*)((size_t)&obj + _Offset)) = Val; }
	private:
		size_t _Offset = 0;
	};
}