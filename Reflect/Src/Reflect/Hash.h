#pragma once
#include<iostream>
template <typename T>
inline size_t hash_combine(const size_t& seed, const T& val)
{
	std::hash<T> hasher;
	return seed ^ (hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}
template<typename Type>
struct TypeHash
{
	size_t operator()()const
	{
		return typeid(Type).hash_code();
	}
};
template<typename Class, typename Ret, typename ...Args>
struct MebFunHash
{
	size_t operator()(Ret(Class::* MebFun)(Args...))const
	{
		size_t seed = TypeHash<Class>()();
		return hash_combine(seed, std::string(typeid(MebFun).raw_name()));
	}
	size_t operator()(Ret(Class::* MebFun)(Args...) const) const {
		size_t seed = TypeHash<Class>()();
		return hash_combine(seed, std::string(typeid(MebFun).raw_name()));
	}
};