#pragma once
#include <string>
#include<functional>
#include<any>
namespace reflect
{
	class MemberVariable 
	{
		friend class RawTypeDescriptorBuilder;
	public:
		MemberVariable()
		{

		}

		template<class Class, typename Var>
		MemberVariable(Var Class::* var) 
		{                                           
			m_Getter = [var](std::any obj) -> std::any 
			{
				return std::any_cast<const Class*>(obj)->*var;
			};

			m_Setter = [var](std::any obj, std::any val) 
			{
				auto* self = std::any_cast<Class*>(obj);
				self->*var = std::any_cast<Var>(val);
			};
		}

		const std::string& GetName() const 
		{
			return m_Name;
		}

		template<typename Var, class Class>
		Var GetValue(const Class& obj) const 
		{
			return std::any_cast<Var>(m_Getter(&obj));
		}

		template<typename Var, class Class>
		void SetValue(Class& obj, Var value) 
		{
			m_Setter(&obj, value);
		}

	private:
		std::string m_Name;
		std::function<std::any(std::any)> m_Getter{ nullptr };
		std::function<void(std::any, std::any)> m_Setter{ nullptr };
	};
}