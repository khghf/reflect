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
		template<typename VarType,typename Class>
		VarType GetValue(Class& obj)const { return *(VarType*)((size_t)&obj + _Offset); }
		template<typename VarType,typename Class>
		void SetValue(Class& obj, const VarType& Val) { 
			using RawVarType = std::remove_reference_t<VarType>;
			(*(RawVarType*)((size_t)&obj + _Offset)) = Val;
		}
	private:
		size_t _Offset = 0;
	};
}