#pragma once
#include <any>
#include <functional>
#include <array>
#include <tuple>
#include <stdexcept>
#include "ArgWrap.h"
namespace reflect
{
	class MemberFunction
	{
		friend class RawTypeDescriptorBuilder;
	public:
		MemberFunction() = default;
		//无返回值，非const成员函数
		template<class Class, typename... Args>
		explicit MemberFunction(void (Class::* func)(Args...))
		{
			m_ArgNum = sizeof...(Args);
			m_Function = [func](void* argsPtr) -> std::any
			{
				auto& args = *static_cast<std::array<ArgWrap, sizeof...(Args) + 1>*>(argsPtr);
				auto tp = AsTuple<Class&, Args...>(args);
				std::apply(func, tp);
				return std::any{};
			};
		}
			//无返回值，const成员函数
		template<class Class, typename... Args>
		explicit MemberFunction(void (Class:: * func)(Args...) const)
		{
			m_ArgNum = sizeof...(Args);
			m_Function = [func](void* argsPtr) -> std::any
			{
				auto& args = *static_cast<std::array<ArgWrap, sizeof...(Args) + 1>*>(argsPtr);
				auto tp = AsTuple<Class&, Args...>(args);
				std::apply(func, tp);
				return std::any{};
			};
		}
		//有返回值，非const成员函数
		template<class Class, typename Return, typename... Args>
		explicit MemberFunction(Return(Class:: * func)(Args...))
		{
			m_ArgNum = sizeof...(Args);
			m_Function = [func](void* argsPtr) -> std::any
			{
				auto& args = *static_cast<std::array<ArgWrap, sizeof...(Args) + 1>*>(argsPtr);
				auto tp = AsTuple<Class&, Args...>(args);
				return std::apply(func, tp);
			};
		}
		//有返回值，const成员函数
		template<class Class, typename Return, typename... Args>
		explicit MemberFunction(Return(Class:: * func)(Args...) const)
		{
			m_ArgNum = sizeof...(Args);
			m_Function = [func](void* argsPtr) -> std::any
			{
				auto& args = *static_cast<std::array<ArgWrap, sizeof...(Args) + 1>*>(argsPtr);
				auto tp = AsTuple<Class&, Args...>(args);
				return std::apply(func, tp);
			};
		}

		template<class Class, typename... Args>
		std::any Invoke(Class & obj, Args&&... args)
		{
			if (m_ArgNum != sizeof...(Args))
			{
				throw std::runtime_error("Mismatching number of arguments");
			}
			std::array<ArgWrap, sizeof...(Args) + 1> argsArray = 
			{
				ArgWrap(obj),
				ArgWrap(std::forward<Args>(args))...
			};
			return m_Function(&argsArray);
		}

		std::string GetName()const { return m_Name; }
	private:
		std::string m_Name;
		std::function<std::any(void*)>m_Function;
		int m_ArgNum = 0;
	};

}