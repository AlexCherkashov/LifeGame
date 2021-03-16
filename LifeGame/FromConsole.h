#pragma once
#include <string>

enum Choice {
	Yes = 1,
	No
};

void FromConsole();
void SetPoints(int width, int heigth);
int GetCorrectInt();
int GetCoordinate(char type, int index, int length);
int GetBorder(std::string name);