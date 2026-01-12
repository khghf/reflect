#pragma once
#include"TypeDescriptor .h"
#include<memory>
#include<unordered_map>
namespace reflect
{
	class ReflectInfoRegistry {
	public:
		static ReflectInfoRegistry& Instance() 
		{
			static ReflectInfoRegistry instance;
			return instance;
		}

		std::vector<TypeDescriptor*> Get() const 
		{
			std::vector<TypeDescriptor*> tmpDescs;
			for (auto& desc : m_Descs) 
			{
				tmpDescs.push_back(desc.second.get());
			}
			return tmpDescs;
		}

		TypeDescriptor* Find(const std::string& name) const 
		{
			return m_Descs.find(name)->second.get();
		}

		void Register(std::unique_ptr<TypeDescriptor> desc) 
		{
			auto name = desc->GetName();
			m_Descs[name] = std::move(desc);
		}

		void Clear() 
		{
			decltype(m_Descs) temp;
			m_Descs.swap(temp);
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<TypeDescriptor>> m_Descs;
	};
}