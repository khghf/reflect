#pragma once
#include<string>
#include<clang-c/Index.h>
#include<vector>
namespace reflect
{
	class Util
	{
	public:
		static std::string DisplayName(CXCursor cursor);
		static std::string CursorSpelling(CXCursor cursor);
		static std::string CursorTypeSpelling(CXCursor cursor);
		static std::string TypeSpelling(CXType type);

		static bool CretaFloderIfNotExist(const std::string folderPath);
		static bool IsFileExist(const std::string filePath);
		static std::string GetFileSuffix(const std::string& path);
		static std::string GetFileName(const std::string& filePath, bool bWithSuffix);
		static std::vector<std::string>GetAllFilePath(const std::string& FloderPath, bool GetSubFloderFile = false);
	};

}