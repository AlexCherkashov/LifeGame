#include <set>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Algorithm.h"

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
	set<int> hashes{};
	int correntHash{};
	hashes.insert(GetHashArray(field, width, heigth));

	PrintField(field, width, heigth);
	while (true) {
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < heigth; j++) {
				LiveOrDieCell(field, newfield, i, j);
			}
		}
		for (int i = 1; i < width - 1; ++i) {
			for (int j = 1; j < heigth - 1; ++j) {
				field[i][j] = newfield[i][j];
			}
		}
		if (!isContinue()) 
			return;
		PrintField(field, width, heigth);
		correntHash = GetHashArray(field, width, heigth);
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
					return;
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
}

void PrintField(int** field, int width, int heigth) {
	system("cls");
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
	int coutNeighbor{};
	for (int n = i - 1; n <= i + 1; ++n) {
		for (int m = j - 1; m <= j + 1; ++m) {
			coutNeighbor += field[n][m];
		}
	}
	coutNeighbor -= field[i][j];
	if (coutNeighbor == 3 && field[i][j] == Dead)
		newfield[i][j] = Alive;
	if ((coutNeighbor < 2 || coutNeighbor > 3) && field[i][j] == Alive)
		newfield[i][j] = Dead;
}

int GetHashArray(int** field, int width, int heigth) {
	unsigned int hashX{};
	unsigned int hashY{};

	for (int i = 1; i < width - 1; i++) {
		unsigned int x{};
		for (int j = 1; j < heigth - 1; j++) {
			x += field[i][j] * j;
		}
		hashX += x * i;
	}

	for (int j = 1; j < heigth - 1; j++) {
		unsigned int y{};
		for (int i = 1; i < width - 1; i++) {
			y += field[i][j] * i;
		}
		hashY += y * j;
	}

	return (hashX * 2) + hashY;
}


bool isContinue() {
	char key{};
	while (true) {
		key = _getch();
		switch (key)
		{
		case Continue:
			system("cls");
			return (true);
		case Exit:
			return (false);
		default:
			cout << "Неверно, нажмите пробел чтобы продолжить или ESC чтобы выйти" << endl;
			break;
		}
	}
}