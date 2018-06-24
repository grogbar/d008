#include "toolkit.h"

int icompare(std::string s1, std::string s2)
{
	std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	return s1.compare(s2);
}

std::string trim(const std::string& str,
	const std::string& whitespace )
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

std::string GetCurrentWorkingDir(void) {
	// #include <stdio.h>
	// #include <direct.h>
	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

std::string upper(std::string s1) {
	std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
	return s1;
}

std::string lower(std::string s1) {
	std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	return s1;
}

