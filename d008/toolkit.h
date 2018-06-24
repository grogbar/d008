#pragma once
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <direct.h>

int icompare(std::string s1, std::string s2);
std::string upper(std::string);
std::string lower(std::string);
std::string trim(const std::string& str, const std::string& whitespace = " \t\r\n"); // default whitespace = " \t\r\n"
std::string GetCurrentWorkingDir(void);

