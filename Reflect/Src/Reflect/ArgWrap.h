#pragma once
#include<any>
#include<array>
#include<tuple>
#include<stdexcept>
namespace reflect
{
	template<typename T>
	struct RefTrait {
		static constexpr int value = 0;
	};
	template<typename T>
	struct RefTrait<T&> {
		static constexpr int value = 1;
	};
	template<typename T>
	struct IsConst : std::false_type {};

	template<typename T>
	struct IsConst<T&> : std::false_type {};

	template<typename T>
	struct IsConst<T*> : std::false_type {};

	template<typename T>
	struct IsConst<const T> : std::true_type {};

	template<typename T>
	struct IsConst<const T&> : std::true_type {};

	template<typename T>
	struct IsConst<const T*> : std::true_type {};



	//std::make_tuple默认会把每个参数进行一次拷贝，将其转化为原始值类型，为了防止被元组还原成原始类型需要进行一层包装，再通过Cast转换回去
	//包装的参数为左值引用是，storage是指针
	//包装的参数为非左值引用时，storage是值类型(避免传递右值参数时的悬垂引用)
	class ArgWrap {
	public:
		template<typename T>
		ArgWrap(T&& value) {
			refType = RefTrait<T>::value;
			isConst = IsConst<T>::value;

			if (refType == 1) {
				storage = &value;
			}
			else {
				storage = value;
			}
		}
		//将被擦除后的参数转换回原类型
		template<typename T>
		T Cast() {
			//去掉类型的const限定符和volatile限定符
			using RawT = std::remove_cv_t<std::remove_reference_t<T>>;
			constexpr int castRefType = RefTrait<T>::value;//想要转换成的类型是否为引用类型
			constexpr bool castIsConstant = IsConst<T>::value;//是否被const修饰
			

			//转换成非引用类型
			if constexpr (castRefType == 0) 
			{
				if (refType == 1) 
				{
					//引用类型转换为值类型
					if (isConst)
						return *std::any_cast<const RawT*>(storage);
					else
						return *std::any_cast<RawT*>(storage);
				}
				//值类型转换为值类型
				return std::any_cast<RawT>(storage);
			}

			//值类型转换为引用类型
			if (refType == 0) 
			{
				return *std::any_cast<RawT>(&storage);
			}

			//引用类型转换为引用类型
			if constexpr (castIsConstant) 
			{
				if (isConst)
					return *std::any_cast<const RawT*>(storage);
				else
					return *std::any_cast<RawT*>(storage);
			}
			else 
			{
				if (isConst) 
				{
					//无法将常量引用转换为非常量引用
					throw std::runtime_error("Cannot cast const ref to non-const ref");
				}
				return *std::any_cast<RawT*>(storage);
			}
		}
	private:
		int refType{ 0 };//是否为引用类型
		bool isConst{ false };//是否被const修饰
		std::any storage{};//1为指针类型，0为值类型
	};
	//将被类型擦除的参数转换回原本的类型
	template<typename... Args, size_t N, size_t... Is>
	std::tuple<Args...> AsTuple(std::array<ArgWrap, N>& array, std::index_sequence<Is...>)
	{
		return std::forward_as_tuple(array[Is].template Cast<Args>()...);
	}

	template<typename... Args, size_t N, typename = std::enable_if_t<N == sizeof...(Args)>>
	std::tuple<Args...> AsTuple(std::array<ArgWrap, N>& array)
	{
		return AsTuple<Args...>(array, std::make_index_sequence<N>());
	}


}

