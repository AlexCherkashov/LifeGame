#include <set>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Algorithm.h"
#include "CinClear.h"
#include "SaveToFile.h"

using namespace std;

void GenerateLife(int** field, int width, int heigth) {
	char key{};
	int** newfield = new int* [width];
	for (int i = 0; i < width; ++i) {
		newfield[i] = new int[heigth];
		for (int j = 0; j < heigth; ++j) {
			newfield[i][j] = field[i][j];
		}
	}
	set<unsigned int> hashes{};
	unsigned int correntHash{};
	hashes.insert(GetMatrixHash(field, width, heigth));

	system("cls");
	cout << "Для продолжения нажмите пробел, чтобы выйти нажмите ESC" << endl;
	PrintField(field, width, heigth);
	bool isContinue = true;
	while (isContinue) {
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < heigth - 1; j++) {
				LiveOrDieCell(field, newfield, i, j);
			}
		}
		for (int i = 1; i < width - 1; ++i) {
			for (int j = 1; j < heigth - 1; ++j) {
				field[i][j] = newfield[i][j];
			}
		}
		if (!IsContinue())
			break;

		system("cls");
		cout << "Для продолжения нажмите пробел, чтобы выйти нажмите ESC" << endl;
		PrintField(field, width, heigth);
		correntHash = GetMatrixHash(field, width, heigth);
		if (hashes.count(correntHash) != 0) {
			cout << "Замечен цикл, будете продолжать?" << endl
				<< "Пробел - Да\nESC - Нет" << endl;
			bool isNotOk = true;
			while (isNotOk) {
				key = _getch();
				switch (key)
				{
				case Continue:
					isNotOk = false;
					cout << "Хорошо, нажмите пробел чтобы продолжить" << endl;
					break;
				case Exit:
					isContinue = false;
					isNotOk = false;
					break;
				default:
					cout << "Неверно, нажмите пробел чтобы продолжить или ESC чтобы выйти" << endl;
					break;
				}
			}
		}
		else {
			hashes.insert(correntHash);
		}
	}

	if (ChoiceToSave("результат работы")) {
		set<pair<int, int>> inputPoints{};
		for (int i = 1; i < width - 1; ++i) {
			for (int j = 1; j < heigth - 1; ++j) {
				if (field[i][j] == Alive)
					inputPoints.insert(make_pair(i - 1, j - 1));
			}
		}
		SaveToFile(width, heigth, inputPoints);
	}

	for (int i = 0; i < width; i++)
		delete[] newfield[i];
	delete[] newfield;
}

void PrintField(int** field, int width, int heigth) {

	for (int i = 1; i < width - 1; ++i) {
		for (int j = 1; j < heigth - 1; ++j) {
			if (field[i][j] == Alive)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
}

void LiveOrDieCell(int** field, int** newfield, int i, int j) {
	int countNeighbor{};
	for (int n = i - 1; n <= i + 1; ++n) {
		for (int m = j - 1; m <= j + 1; ++m) {
			countNeighbor += field[n][m];
		}
	}
	countNeighbor -= field[i][j];
	if (countNeighbor == 3 && field[i][j] == Dead)
		newfield[i][j] = Alive;
	if ((countNeighbor < 2 || countNeighbor > 3) && field[i][j] == Alive)
		newfield[i][j] = Dead;
}

unsigned int GetMatrixHash(int** field, int width, int heigth) {
	unsigned int hashX{};
	unsigned int hashY{};

	for (int i = 1; i < width - 1; i++) {
		unsigned int x{};
		for (int j = 1; j < heigth - 1; j++) {
			x += field[i][j] * pow(2, j - 1);
		}
		hashX += x ^ i;
	}

	for (int j = 1; j < heigth - 1; j++) {
		unsigned int y{};
		for (int i = 1; i < width - 1; i++) {
			y += field[i][j] * pow(2, i - 1);
		}
		hashY += y ^ j;
	}

	return hashX ^ hashY;
}


bool IsContinue() {
	char key{};
	while (true) {
		key = _getch();
		switch (key)
		{
		case Continue:
			system("cls");
			return true;
		case Exit:
			return false;
		default:
			cout << "Неверно, нажмите пробел чтобы продолжить или ESC чтобы выйти" << endl;
			break;
		}
	}
}