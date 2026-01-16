#include "CodeGrenerator.h"
#include"../Meta/MetaInfo.h"
#include<string>
#include<string_view>
#include"../Util.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<regex>
namespace reflect
{
	std::string CodeGrenerator::FileStorageFloder = "";
	std::string_view GeneratedCppIncludes = "Src/Reflect/GeneratedCppIncludes.h";
	const MetaFile* Info = nullptr;
	void CodeGrenerator::GenerateCode()
	{
		Util::CretaFloderIfNotExist(FileStorageFloder);
		for (const auto& it : MetaInfo::GetMetaRegistry())
		{
			Info = &it.second;
			Generate_h();
			Generate_cpp();
		}
	}

	void CodeGrenerator::Generate_h()
	{

		const std::string fileName = Util::GetFileName(Info->Path, false)+".gen.h";

		std::string savePath = FileStorageFloder.data();
		savePath = savePath + "/"+ fileName;
		std::string includePath = include_angled(savePath);
		Push_backIncludeToFile(Util::ModifySuffix(Info->Path, "h"), includePath.substr(0, includePath.size()-1));
		std::ofstream out(savePath, std::ios_base::trunc);
		std::stringstream content;
		content << "#pragma once\n";
		for (const auto& metaClass : Info->Classes)
		{
			const std::string& className = metaClass.Name;
			const std::string opertaorName = "AAA_" + className + "_Operator";
			if (metaClass.ReflectBodyLine == "-1")
			{
				std::cerr << "ERROR:Marco REFLECT_BODY must be used in reflection class " + className << std::endl;
			}
			else
			{

				content << "class " + opertaorName + ";\n";
				content << "#define REFLECT_BODY_" + metaClass.ReflectBodyLine + "()\\\n";
				content << "friend class "+ opertaorName+";\n";
			}
		}
		out << content.str();
	}

	void CodeGrenerator::Generate_cpp()
	{
		const std::string fileName = Util::GetFileName(Info->Path, false) + ".gen.cpp";
		std::string savePath = FileStorageFloder.data();
		savePath = savePath + "/" + fileName;

		std::ofstream out(savePath, std::ios_base::trunc);
		std::stringstream content;
		content << include_quotes(GeneratedCppIncludes.data());
		content << include_quotes( Util::ModifySuffix(Info->Path,"h"));

		const std::string rclass = "reflect::RClass";
		const std::string rfunction = "reflect::RFunction";
		const std::string rproperty = "reflect::RProperty";

		//content << "using namespace reflect;\n";
		for (const auto& metaClass : Info->Classes)
		{
			
			const std::string& className = metaClass.Name;
			//AAA_XXX_Operator,用于访问类的私有成员
			int nameSpaceCount = metaClass.NameSpaces.size();
			std::string nameSpace = "";
			if (nameSpaceCount > 0)
			{
				for (int i = nameSpaceCount - 1; i >= 0; --i)
				{
					if (i != 0)
					{
						nameSpace += metaClass.NameSpaces[i] + "::";
					}
					else
					{
						nameSpace += metaClass.NameSpaces[i];
					}
				}
			}
			const std::string opertaorName= "AAA_" + className + "_Operator";
			content << "class "+opertaorName + "\n";
			content << "{\n";
			content << "public:\n";
			content << "\tConstructRClass(" + className +","+nameSpace+ ")\n";
			for (const auto& metaFun : metaClass.Functions)
			{
				const std::string& funName = metaFun.Name;
				content << "\tConstructRFunction(" + funName + "," + className + "," + nameSpace + ")\n";
			}
			for (const auto& metaProperty : metaClass.Properties)
			{
				const std::string& proName = metaProperty.Name;
				content << "\tConstructRProperty(" + proName + "," + className + "," + nameSpace + ")\n";
			}
			content << "};\n";

			//将AAA_XXX_Operator内部的函数包装成普通函数
			content << rclass+"*AAA_Construct_RClass_" + className + "()\n";
			content << "{\n";
			content << "\treturn "+opertaorName+"::ConstructRClass_"+className + "(); \n";
			content << "}\n";
			for (const auto& metaFun : metaClass.Functions)
			{
				const std::string& funName = metaFun.Name;
				content << rfunction+"*AAA_Construct_RFunction_" + funName + "()\n";
				content << "{\n";
				content << "\treturn " + opertaorName + "::ConstructRFunction_" + funName + "();\n";
				content << "}\n";

			}
			for (const auto& metaProperty : metaClass.Properties)
			{
				const std::string& proName = metaProperty.Name;
				content << rproperty+"*AAA_Construct_RProperty_" + proName + "()\n";
				content << "{\n";
				content << "\treturn " + opertaorName + "::ConstructRProperty_" + proName + "();\n";
				content << "}\n";
			}
			//将信息收集到AAA_Construct_XXX_Statics中
			content << "struct AAA_Construct_" + className + "_Statics\n";
			content << "{\n";
			content << "\tstatic RClassConstructor RClass_" + className + "_Constructor;\n";
			if(metaClass.Functions.size()>0)content << "\tstatic RFunctionConstructor RFunction_" + className + "_Constructor[];\n";
			if (metaClass.Properties.size() > 0)content << "\tstatic RPropertyConstructor RProperty_" + className + "_Constructor[];\n";
			content << "\tconst static uint32_t FunctionNum;\n";
			content << "\tconst static uint32_t PropertyNum;\n";
			content << "};\n";
				//RClass
			content << "RClassConstructor AAA_Construct_" + className + "_Statics::RClass_" + className + "_Constructor = AAA_Construct_RClass_" + className + ";\n";
				//RFunctions
			if (metaClass.Functions.size() > 0)
			{
				content << "RFunctionConstructor AAA_Construct_" + className + "_Statics::RFunction_" + className + "_Constructor[]=\n";
				content << "{\n";
				for (const auto& metaFun : metaClass.Functions)
				{
					const std::string& funName = metaFun.Name;
					content << "\tAAA_Construct_RFunction_" + funName + ",\n";

				}
				content << "};\n";
			}
				//RProperties
			if (metaClass.Properties.size() > 0)
			{
				content << "RPropertyConstructor AAA_Construct_" + className + "_Statics::RProperty_" + className + "_Constructor[]=\n";
				content << "{\n";
				for (const auto& metaPro : metaClass.Properties)
				{
					const std::string& proName = metaPro.Name;
					content << "\tAAA_Construct_RProperty_" + proName + ",\n";

				}
				content << "};\n";
			}
				//FunctionNum
			if (metaClass.Functions.size() > 0)content << "const uint32_t AAA_Construct_" + className + "_Statics::FunctionNum = ARRAY_COUNT(AAA_Construct_" + className + "_Statics::RFunction_" + className + "_Constructor);\n";
			else content << "const uint32_t AAA_Construct_" + className + "_Statics::FunctionNum = 0;\n";
				//PropertyNum
			if (metaClass.Properties.size() > 0)content << "const uint32_t AAA_Construct_" + className + "_Statics::PropertyNum = ARRAY_COUNT(AAA_Construct_" + className + "_Statics::RProperty_" + className + "_Constructor);\n";
			else content << "const uint32_t AAA_Construct_" + className + "_Statics::PropertyNum = 0;\n";
			//将收集的信息转发注册
			content << "static RegistrationInfo Collector_" + className + "=\n";
			content << "{\n";
			content << "\tAAA_Construct_" + className + "_Statics::RClass_" + className + "_Constructor,\n";
			if (metaClass.Functions.size() > 0)content << "\tAAA_Construct_" + className + "_Statics::RFunction_" + className + "_Constructor,\n";
			else content << "\tnullptr,\n";
			if (metaClass.Properties.size() > 0)content << "\tAAA_Construct_" + className + "_Statics::RProperty_" + className + "_Constructor,\n";
			else content << "\tnullptr,\n";
			content << "\tAAA_Construct_" + className + "_Statics::FunctionNum,\n";
			content << "\tAAA_Construct_" + className + "_Statics::PropertyNum\n";
			content << "};\n";
			content << "static CollectRegistrationInfo Register (Collector_" + className + ");\n";
		}
		out << content.str();
	}

	const std::string CodeGrenerator::include_angled(const std::string& path)
	{
		return "#include<" + path + ">\n";
	}

	const std::string CodeGrenerator::include_quotes(const std::string& path)
	{
		return "#include\"" + path + "\"\n";
	}

	void CodeGrenerator::Push_backIncludeToFile(const std::string& filePath, const std::string& includestr)
	{
		std::ifstream file(filePath, std::ios::in);
		//先去掉可能存在的想要插入的头文件
		std::stringstream steam;
		steam << file.rdbuf();
		std::string content = steam.str();
		Util::RemoveUtf8Bom(content);
		uint32_t includeNumBefore = Util::GetIncludeNumInStr(content);
		std::regex includeRe(R"(\\)",std::regex::nosubs);
		const std::string includeStrModified = std::regex_replace(includestr, includeRe, R"(\\)") + "(\n|\r)*";
		std::regex re(includeStrModified, std::regex::nosubs);
		if (std::regex_search(content, re))
		{
			content = std::regex_replace(content, re, "");
			file.close();
			std::ofstream out(filePath, std::ios_base::trunc);
			out << content;
			out.close();

			file.open(filePath);

		}
		uint32_t includeNumAfter = Util::GetIncludeNumInStr(content);
		Util::SkipUtf8Bom(file);
		std::vector<std::string> fileLines;
		std::string line;
		uint32_t CurLine = 0;
		bool bPushed = false;
		while (std::getline(file, line)) {
			++CurLine;
			if (CurLine > (Info->LastIncludeLine+(includeNumAfter-includeNumBefore))&&!bPushed)
			{
				bPushed = true;
				fileLines.emplace_back(includestr+"\n");
			}
			fileLines.emplace_back(std::move(line) + "\n");
		}
		file.close();
		std::ofstream out(filePath, std::ios_base::trunc);
		for (const auto& str : fileLines)
		{
			out << str;
		}
		out.close();
	}

}