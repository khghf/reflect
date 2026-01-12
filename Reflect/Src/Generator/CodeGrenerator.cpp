#include "CodeGrenerator.h"
#include<Meta/MetaInfo.h>
#include<string>
#include<string_view>
#include"Util.h"
#include<iostream>
#include<fstream>
#include<sstream>

namespace reflect
{
	std::string_view FileStorageFloder = "GeneratedReflectionCode";
	const MetaFile* Info = nullptr;
	void CodeGrenerator::GenerateCode()
	{
		Util::CretaFloderIfNotExist(FileStorageFloder.data());
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
		std::ofstream out(savePath,std::ios_base::trunc);
		std::stringstream content;
		content << "#pragma once\n";
		out << content.str();
	}

	void CodeGrenerator::Generate_cpp()
	{
		const std::string fileName = Util::GetFileName(Info->Path, false) + ".gen.cpp";
		std::string savePath = FileStorageFloder.data();
		savePath = savePath + "/" + fileName;
		std::ofstream out(savePath, std::ios_base::trunc);
		std::stringstream content;
		content<< Util::GetFileName(Info->Path, false) + ".gen.h";
		out << content.str();
	}
}