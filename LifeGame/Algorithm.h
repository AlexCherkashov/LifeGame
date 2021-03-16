#pragma once
enum Life {
	Dead,
	Alive,
	Border,
	Continue = 32,
	Exit = 27
};

void GenerateLife(int** field, int width, int length);
void PrintField(int** field, int width, int length);
unsigned int GetHashArray(int** field, int width, int heigth);
void LiveOrDieCell(int** field, int** newfield, int i, int j);
bool isContinue();