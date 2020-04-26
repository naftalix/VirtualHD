#include "Functions.h"
#include<ctime>
#pragma warning(disable: 4996)

namespace Fms{

	std::string getDate(){
		time_t rawtime;
		struct tm * timeinfo;
		char result[10];
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		strftime(result, 10, "%d%m%Y", timeinfo);
		return std::string(result);
	}

	std::wstring stringToWString(const std::string& s){
		return std::wstring(s.begin(), s.end());
	}

	std::string convertDate(const char date[]){
		std::string result;
		result += date[0];
		result += date[1];
		result += '/';
		result += date[2];
		result += date[3];
		result += '/';
		result += date[4];
		result += date[5];
		result += date[6];
		result += date[7];

		return result;
	}

	const std::string removePath(const std::string& fileName){
		const int sz = static_cast<int>(fileName.size());
		const int path_sz = fileName.rfind("\\",fileName.size());
		std::string tmpName;
		if (path_sz == sz) tmpName = fileName;
		else tmpName = fileName.substr(path_sz + 1,sz - 1 - path_sz);
		const int path_sz1 = fileName.rfind("/",fileName.size());
		if (path_sz == sz) return tmpName;
		return tmpName.substr(path_sz1 + 1,sz - 1 - path_sz1);
	}

}