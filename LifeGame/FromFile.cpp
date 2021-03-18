#include <string>
#include <iostream>
#include <fstream>
#include "CinClear.h"
#include "CheckFileName.h"
#include "Algorithm.h"
#include "FromFile.h"

using namespace std;

void FromFile() {
	vector<int> input;
	bool isNotCorrectInput = true;
	string path;
	while (isNotCorrectInput) {
		cout << "Введите адрес файла в формате .txt:" << endl;
		cin >> path;
		cout << endl;
		CinClear();

		if (check_reg(path) && isExist(path)) {
			isNotCorrectInput = !GetDataFormFile(path, input);
		}
		else {
			isNotCorrectInput = true;
		}
		if (!isNotCorrectInput) {
			isNotCorrectInput = !IsCorrectData(input);
		}
	}

	int width = input.at(0) + 2;
	int heigth = input.at(1) + 2;

	int** field = new int* [width];
	for (int i = 0; i < width; i++) {
		field[i] = new int[heigth];
		for (int j = 0; j < heigth; j++) {
			field[i][j] = Dead;
		}
	}

	vector<pair<int, int>> inputPoints{};
	for (size_t i = 2; i < input.size(); i += 2) {
		int x = input.at(i);
		int y = input.at(i + 1);
		inputPoints.emplace_back(make_pair(x, y));
	}

	for (auto& point : inputPoints) {
		field[point.first + 1][point.second + 1] = Alive;
	}

	GenerateLife(field, width, heigth);
	for (int i = 0; i < width; i++)
		delete[] field[i];
	delete[] field;
}

bool GetDataFormFile(const string& path, vector<int>& input) {
	ifstream stream;
	stream.open(path);
	string line;
	while (getline(stream, line)) {
		try {
			input.emplace_back(stoi(line));
		}
		catch (invalid_argument) {
			cout << "Файл содержит нечисловые значения, выберите другой" << endl;
			stream.close();
			return false;
		}
		catch (out_of_range) {
			cout << "Файл содержит значение, выходящие за пределы int" << endl;
			stream.close();
			return false;
		}
	}
	stream.close();

	if (input.empty()) {
		cout << "Файл пустой, выберите другой файл" << endl;
		return false;
	}

	return true;
}

bool IsCorrectData(vector<int>& input) {
	if (input.size() % 2 != 0) {
		cout << "В файле должно быть чётное количество чисел" << endl;
		return false;
	}
	if (input.size() < 4) {
		cout << "В файле слишком мало чисел, должно быть минимум 4" << endl;
		return false;
	}

	int width = input.at(0);
	int heigth = input.at(1);

	if (width < 3) {
		cout << "Ширина (первое значение) должно быть больше или равно 3м" << endl;
		return false;
	}
	if (heigth < 3) {
		cout << "Высота (второе значение) должно быть больше или равно 3м" << endl;
		return false;
	}

	if (width > 32) {
		cout << "Ширина (первое значение) должно быть меньше или равно 32м" << endl;
		return false;
	}
	if (heigth > 32) {
		cout << "Высота (второе значение) должно быть меньше или равно 32м" << endl;
		return false;
	}

	if (width * heigth < ((input.size() - 2) / 2)) {
		cout << "В файле слишком много значений" << endl;
		return false;
	}

	for (int i = 2; i < input.size(); i += 2) {
		int x = input.at(i);
		int y = input.at(i + 1);

		if (x >= width) {
			cout << "В " << (i + 1) << "й строке значение больше ширины" << endl;
			return false;
		}
		if (x >= heigth) {
			cout << "В " << (i + 2) << "й строке значение больше высоты" << endl;
			return false;
		}
	}
	return true;
}