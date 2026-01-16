#pragma once
#include<string>
#include<vector>
#include<unordered_map>
#include<stdexcept>
//存储通过CodeParser收集的信息，然后用于生成代码
namespace reflect
{
	struct MetaProperty
	{
		explicit MetaProperty(const std::string& name) :Name(name) {}
		std::string Name;
		std::string TypeName;
		std::string ClassName;
	};
	struct MetaFunction
	{
		explicit MetaFunction(const std::string& name) :Name(name) {}
		std::string Name;
		std::string ReturnName;
		std::vector<std::pair<std::string, std::string>>Type_ParamName;

		std::string ClassName;
	};
	struct MetaClass
	{
		explicit MetaClass(const std::string& name) :Name(name) {}
		std::string Name;
		std::vector<MetaFunction>Functions;
		std::vector<MetaProperty>Properties;
		std::string FilePath;
		std::vector<std::string>NameSpaces;
		std::string ReflectBodyLine = "-1";
	};
	struct MetaFile
	{
		explicit MetaFile(const std::string& name) :Path(name) {}
		std::string Path;
		std::vector<MetaClass>Classes;
		std::vector<uint32_t>ReflectBodyMarcoLine;
		uint32_t CurClassMarcoIndex = 0;
		uint32_t LastIncludeLine = 0;
		MetaClass& GetMetaClass(const std::string&className)
		{
			for (auto& it : Classes)
			{
				if (it.Name == className)return it;
			}
			throw std::runtime_error("No classes to register in"+Path);
		}
		bool HasMetaClass(const std::string& className)const
		{
			for (const auto& it : Classes)
			{
				if (it.Name == className)return true;
			}
			return false;
		}
	};
	class MetaInfo
	{
	public:
		static MetaFile*		RegisterMetaFile(MetaFile& meta);
		static MetaClass*		RegisterMetaClass(MetaClass& meta);
		static void				RegisterMetaFunction(MetaFunction& meta);
		static void				RegisterMetaProperty(MetaProperty& meta);
		static bool				HasMetaFile(std::string& filePath);
		static void				ClearMetaInfo();
		static std::unordered_map<std::string, MetaFile>& GetMetaRegistry();
		static void			Test();
	};
}
