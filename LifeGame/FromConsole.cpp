#include <iostream>
#include "CinClear.h"
#include "Algorithm.h"
#include "FromConsole.h"
#include "SaveToFile.h"
#include "UnknownCommand.h"
#include <vector>
#include <set>

using namespace std;

void FromConsole() {
	int heigth = GetBorder("ширину");
	int width = GetBorder("высоту");;
	heigth += Border;
	width += Border;
	SetPoints(width, heigth);
}

int GetBorder(string name) {
	int value{};
	while (true) {
		cout << "Введите " << name << " поля (минимум 3, максимум 32)" << endl;
		value = GetCorrectInt();
		if (value < 3) {
			cout << "Число должно быть больше или равно 3" << endl;
		}
		else if (value > 32) {
			cout << "Слишком большое значение, введите другое" << endl;
		}
		else {
			break;
		}
	}
	return value;
}

int GetCorrectInt() {
	int a{};
	while (true) {
		cin >> a;
		if (cin.good()) {
			break;
		}
		CinClear();
		cout << "Не число! Введите заново:";
	}
	return a;
}

void SetPoints(int width, int heigth) {
	int pointCount;
	cout << "Сколько клеток вы хотите ввести?" << endl;
	while (true) {
		pointCount = GetCorrectInt();
		if (pointCount > (width - 2) * (heigth - 2)) {
			cout << "Максимальное количество клеток: " << (width - 2) * (heigth - 2)
				<< ".\nВведите другой значение" << endl;
		}
		else if (pointCount <= 0) {
			cout << "Минимальное количество клеток: 1\nВведите другой значение" << endl;

		}
		else {
			break;
		}
	}

	int** field = new int* [width];
	for (int i = 0; i < width; i++) {
		field[i] = new int[heigth];
		for (int j = 0; j < heigth; j++) {
			field[i][j] = Dead;
		}
	}

	set<pair<int, int>> inputPoints{};
	for (int i = 0; i < pointCount; i++) {
		while (true) {
			int x = GetCoordinate('X', i, width);
			int y = GetCoordinate('Y', i, heigth);
			auto point = make_pair(x, y);
			if (inputPoints.count(point) != 0) {
				cout << "Вы уже задали такую точку, выберите другую" << endl;
			}
			else {
				inputPoints.insert(point);
				break;
			}
		}
	}

	for (auto& pair : inputPoints) {
		field[pair.first + 1][pair.second + 1] = Alive;
	}

	if (ChoiceToSave())
		SaveToFile(width, heigth, inputPoints);

	GenerateLife(field, width, heigth);
	for (int i = 0; i < width; i++)
		delete[] field[i];
	delete[] field;
}

int GetCoordinate(char type, int index, int length) {
	int coordinate{};
	cout << "Введите координату "<< type <<" у " << (index + 1) << "й точки" << endl;
	while (true) {
		coordinate = GetCorrectInt();
		if (coordinate >= length - Border || coordinate < 0) {
			cout << "Координата выходит за границы" << endl;
		}
		else {
			break;
		}
	}
	return coordinate;
}