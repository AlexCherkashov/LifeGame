#pragma once
#include <string>
#include <vector>

enum Number {
	Zero = 49,
	Nine = 57
};

void str_tolower(std::string& s);
bool check_reg(const std::string& name);
bool isExist(const std::string& path);