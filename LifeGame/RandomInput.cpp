#include "Algorithm.h"
#include "FromConsole.h"
#include <set>
#include <iostream>
#include "UnknownCommand.h"
#include "CinClear.h"
#include "SaveToFile.h"

using namespace std;

void RandomInput() {
	int heigth = GetBorder("ширину");
	int width = GetBorder("высоту");;
	heigth += Border;
	width += Border;

	set<pair<int, int>> inputPoints{};
	int cell{};
	int** field = new int* [width];
	for (int i = 0; i < width; i++) {
		field[i] = new int[heigth];
		for (int j = 0; j < heigth; j++) {
			if ((i > 0 && i < width - 1) && (j > 0 && j < heigth - 1)) {
				cell = rand() % 2;
				if (cell == Alive)
					inputPoints.insert(make_pair(i - 1, j - 1));
				field[i][j] = cell;
			}
			else {
				field[i][j] = Dead;
			}
		}
	}

	cout << endl;
	PrintField(field, width, heigth);

	if (ChoiceToSave("исходные данные"))
		SaveToFile(width, heigth, inputPoints);

	GenerateLife(field, width, heigth);
	for (int i = 0; i < width; i++)
		delete[] field[i];
	delete[] field;
}