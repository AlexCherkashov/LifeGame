#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <filesystem>
#include <windows.h>
#include "CheckFileName.h"

using namespace std;

void SplitePath(const string& path, string& fileName, string& directory) {
	size_t n = path.find_last_of("/\\");
	fileName = path.substr(n + 1);
	directory = path.substr(0, n + 1);
}

bool check_reg(const string& path)
{
	if (path.size() > MAX_PATH) {
		cout << "Слишком длинное имя файла" << endl;
		return false;
	}

	string name;
	string directory;
	SplitePath(path, name, directory);
	str_tolower(name);

	if (!directory.empty()) {
		if (!filesystem::is_directory(directory)) {
			cout << "Такой директории нет" << endl;
			return false;
		}
	}
	if (name.length() < 4) {
		cout << "Это не .txt файл" << endl;
		return false;
	}
	if (name.substr(name.length() - 4) != ".txt") {
		cout << "Это не .txt файл" << endl;
		return false;
	}

	set<char> wrongSymbs = { '/', '\\', ':', '*', '?', '"', '<', '>', '|' };
	for (char& symb : name) {
		if (wrongSymbs.count(symb) != 0) {
			cout << "Имя файла содержит неверные символы" << endl;
			return false;
		}
	}

	string first_four_simbols = name.substr(0, 4);
	set<string> reservedFieNames = { "con.", "prn.", "aux.", "nul." };
	if (reservedFieNames.count(first_four_simbols) != 0) {
		cout << "Это системный файл!" << endl;
		return false;
	}

	string first_three_simbols = name.substr(0, 3);
	if (name.length() >= 8)
		if (((first_three_simbols == "com") || (first_three_simbols == "lpt"))
			&& (name[3] >= Zero) && (name[3] <= Nine) && (name[4] == '.')) {
			cout << "Это системный файл!" << endl;
			return false;
		}

	return(true);
}

void str_tolower(string& s) {
	transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return tolower(c); }
	);
}


bool isExist(const string& path) {
	if (filesystem::exists(path)) {
		return true;
	}
	else {
		cout << "Такого файла нет" << endl;
		return false;
	}
}