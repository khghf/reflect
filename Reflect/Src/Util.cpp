#include"Util.h"
#include<filesystem>

namespace reflect
{
	namespace fs = std::filesystem;

	std::string Util::DisplayName(CXCursor cursor)
	{
		std::string ret;
		CXString str = clang_getCursorDisplayName(cursor);
		ret = clang_getCString(str);
		clang_disposeString(str);
		return ret;
	}

	std::string Util::CursorSpelling(CXCursor cursor)
	{
		std::string ret;
		CXString str = clang_getCursorSpelling(cursor);
		ret = clang_getCString(str);
		clang_disposeString(str);
		return ret;
	}

	std::string Util::CursorTypeSpelling(CXCursor cursor)
	{
		std::string ret;
		CXType type = clang_getCursorType(cursor);
		return TypeSpelling(type);
	}



	std::string Util::TypeSpelling(CXType type)
	{
		std::string ret;
		CXString str = clang_getTypeSpelling(type);
		ret = clang_getCString(str);
		clang_disposeString(str);
		return ret;
	}

	bool Util::CretaFloderIfNotExist(const std::string folderPath)
	{
		fs::path path(folderPath);
		if (fs::exists(path) && fs::is_directory(path))return true;
		return fs::create_directories(path);
	}

	bool Util::IsFileExist(const std::string filePath)
	{
		fs::path path(filePath);
		if (fs::exists(filePath) && fs::is_regular_file(path))return true;
		return false;
	}

	std::string Util::GetFileSuffix(const std::string& path)
	{
		std::string ret=path;
		int index = ret.find_last_of(".");
		if (index+1!=std::string::npos)
		{
			ret = ret.substr(index+1);
		}
		return ret;
	}

	std::string Util::GetFileName(const std::string& filePath, bool bWithSuffix)
	{
		std::string path = filePath;
		int index = -1;
		index = path.find_last_of("/\\");
		if (index+1 != std::string::npos)
		{
			path = path.substr(index + 1);
		}
		if (!bWithSuffix)
		{
			index = path.find_last_of(".");
			if (index != std::string::npos)
			{
				path = path.substr(0, index);
			}
		}
		return path;
	}



	std::vector<std::string> Util::GetAllFilePath(const std::string& FloderPath, bool GetSubFloderFile /*= false*/)
	{
		std::vector<std::string>FilePaths;
		fs::path Path = FloderPath;
		if (!fs::is_directory(Path) || !fs::exists(Path))
		{
			return FilePaths;
		}
		for (const auto& File : fs::directory_iterator(Path))
		{
			if (File.is_regular_file())
			{
				FilePaths.push_back(File.path().string());
			}
			else
			{
				auto SubFiles = GetAllFilePath(File.path().string(), GetSubFloderFile);
				FilePaths.insert(FilePaths.end(), SubFiles.begin(), SubFiles.end());
			}
		}
		return FilePaths;
	}

}