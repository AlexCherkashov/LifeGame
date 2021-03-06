#pragma once
enum Life {
	Dead,
	Alive,
	Border,
	Continue = 32,
	Exit = 27
};

void GenerateLife(int** field, int width, int heigth);
void PrintField(int** field, int width, int heigth);
unsigned int GetMatrixHash(int** field, int width, int heigth);
void LiveOrDieCell(int** field, int** newfield, int i, int j);
bool IsContinue();