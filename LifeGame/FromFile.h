#pragma once
#include <string>
#include <vector>

void FromFile();
bool GetDataFormFile(const std::string& path, std::vector<int>& input);
bool IsCorrectData(std::vector<int>& input);