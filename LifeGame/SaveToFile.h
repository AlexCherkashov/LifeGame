#pragma once
#include <set>

using namespace std;

void SaveToFile(int width, int heigth, set<pair<int, int>> inputPoints);
bool IsContinueToSave();
bool ChoiceToSave(string dataType);