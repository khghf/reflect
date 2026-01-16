#pragma once
#include"RObject.h"
#include<any>
#include<functional>
#include"ArgWrap.h"
#include<array>
namespace reflect
{
	class RClass;
	class RFunction :public RObject
	{
		friend class RObjectSetter;
	public:
		template<typename Class, typename Ret, typename...Args>
		RFunction(Ret(Class::*fun)(Args...))
		{
			_ArgNum = sizeof...(Args);
			_Function = [fun](void* argsPtr) -> std::any
				{
					auto& args = *static_cast<std::array<ArgWrap, sizeof...(Args) + 1>*>(argsPtr);
					auto tp = AsTuple<Class&, Args...>(args);
					std::apply(fun, tp);
					return std::any{};
				};
		}
		template<typename Class, typename Ret, typename...Args>
		RFunction(Ret(Class::* fun)(Args...)const)
		{
			_ArgNum = sizeof...(Args);
			_Function = [fun](void* argsPtr) -> std::any
				{
					auto& args = *static_cast<std::array<ArgWrap, sizeof...(Args) + 1>*>(argsPtr);
					auto tp = AsTuple<Class&, Args...>(args);
					std::apply(fun, tp);
					return std::any{};
				};
		}
	public:
		template<class Class, typename... Args>
		std::any Invoke(Class& obj, Args&&... args)
		{
			if (_ArgNum != sizeof...(Args))
			{
				throw std::runtime_error("Mismatching number of arguments");
			}
			std::array<ArgWrap, sizeof...(Args) + 1> argsArray =
			{
				ArgWrap(obj),
				ArgWrap(std::forward<Args>(args))...
			};
			return _Function(&argsArray);
		}
	private:
		std::function <std::any(void*)> _Function;
		uint8_t _ArgNum;
	};
}