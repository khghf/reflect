#include"Util.h"
#include<filesystem>
#include<regex>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include<iostream>
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

	void Util::GetCursorLocation(CXCursor cursor, uint32_t* out)
	{
		CXSourceLocation location=clang_getCursorLocation(cursor);
		unsigned int line = 0, col = 0;
		clang_getPresumedLocation(location, nullptr, &line, &col);
		out[0] = line;
		out[1] = col;
	}

	void Util::GetCursorLocation(CXCursor cursor, uint32_t* line, uint32_t* col)
	{
		CXSourceLocation location = clang_getCursorLocation(cursor);
		clang_getPresumedLocation(location, nullptr, line, col);
	}

	uint32_t Util::GetIncludeNumInStr(const std::string& str)
	{
		uint32_t res = 0;
		std::regex re(R"(#include(<.*>|".*"))");
		std::sregex_token_iterator it(str.begin(), str.end(), re);
		std::sregex_token_iterator end;
		while (it!=end)
		{
			if (!it->str().empty()) ++res;
			++it;
		}
		return res;
	}

	uint32_t Util::GetIncludeNumInFile(const std::string& filePath)
	{
		std::ifstream file(filePath);
		uint32_t res = 0;
		if (!file.is_open())
		{
			throw std::runtime_error(filePath+"is invalid!");
			return res;
		}
		std::stringstream s;
		SkipUtf8Bom(file);
		s << file.rdbuf();
		const std::string content = s.str();
		return GetIncludeNumInStr(content);
	}

	std::string Util::GetFileSuffix(const std::string& path)
	{
		std::string ret = path;
		int index = ret.find_last_of(".");
		if (index + 1 != std::string::npos)
		{
			ret = ret.substr(index + 1);
		}
		return ret;
	}

	std::string Util::GetFileName(const std::string& filePath, bool bWithSuffix)
	{
		std::string path = filePath;
		int index = -1;
		index = path.find_last_of("/\\");
		if (index + 1 != std::string::npos)
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

	std::string Util::GetStrBehindLastChar(const std::string source, const char* ch)
	{
		std::string ret = source;
		int index = ret.find_last_of(ch);
		if (index != std::string::npos)
		{
			ret = ret.substr(index + 1);
		}
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

	

	std::string Util::ModifySuffix(const std::string& source, const std::string& suffix)
	{
		std::string ret = source;
		int index = ret.find_last_of(".");
		if (index!= std::string::npos)
		{
			ret = ret.substr(0, index + 1);
			ret += suffix;
		}
		else
		{
			ret += ("." + suffix);
		}
		return ret;
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

	bool Util::SkipUtf8Bom(std::ifstream& file)
	{
		const std::vector<unsigned char> UTF8_BOM = { 0xEF, 0xBB, 0xBF };
		if (!file.is_open() || !file.good()) {
			std::cerr << "错误：文件未正常打开，无法检查BOM头" << std::endl;
			return false;
		}
		file.seekg(0, std::ios::beg);
		std::vector<unsigned char> bomCandidate(UTF8_BOM.size());
		file.read(reinterpret_cast<char*>(bomCandidate.data()), bomCandidate.size());
		bool hasUtf8Bom = (bomCandidate == UTF8_BOM);
		if (hasUtf8Bom) {
			return true;
		}
		else {
			file.seekg(0, std::ios::beg);
			return true;
		}
	}

	void Util::RemoveUtf8Bom(std::string& content)
	{
		const char utf8_bom[] = "\xEF\xBB\xBF";
		if (content.size() >= 3 && content.substr(0, 3) == utf8_bom) {
			content.erase(0, 3); // 去掉BOM头
		}
	}

}