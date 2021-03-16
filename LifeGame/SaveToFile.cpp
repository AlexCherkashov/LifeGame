#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "CinClear.h"
#include "FromConsole.h"
#include "CheckFileName.h"
#include "SaveToFile.h"
#include "UnknownCommand.h"

using namespace std;


void SaveToFile(int width, int heigth, set<pair<int, int>> inputPoints) {
	bool isNotCorrectPath = true;
	string path;
	ofstream stream;

	while (isNotCorrectPath) {
		cout << "Введите адрес файла в формате .txt:" << endl;
		cin >> path;
		cout << endl;
		CinClear();
		if (check_reg(path)) {
			if (!filesystem::exists(path)) {
				isNotCorrectPath = false;
			}
			else {
				isNotCorrectPath = !IsContinueToSave();
			}
		}
		else {
			isNotCorrectPath = true;
		}

		if (!isNotCorrectPath) {
			stream.open(path);
			if (!stream) {
				cout << "Файл только для чтения, выберите другой файл" << endl;
				stream.close();
				isNotCorrectPath = true;
			}
		}
	}

	stream << (width - 2) << endl;
	stream << (heigth - 2) << endl;
	for (auto& point : inputPoints) {
		stream << point.first << endl << point.second << endl;
	}
	stream.close();
	cout << "Данные успешно сохранены" << endl;
}

bool IsContinueToSave() {
	int choice;
	while (true) {
		cout << "Такой файл уже есть, перезаписать?" << endl
			<< "1 - Да\n2 - Нет" << endl;
		cin >> choice;
		cout << endl;
		CinClear();
		switch (choice) {
		case 1:
			return (true);
		case 2:
			return (false);
		default:
			UnknownCommand();
		}
	}
}

bool ChoiceToSave() {
	cout << "Будете сохранять исходные данные?" << endl
		<< "1 - Да\n2 - Нет" << endl;
	int choice{};
	while (choice == 0) {
		cin >> choice;
		cout << endl;
		CinClear();
		switch (choice)
		{
		case Yes:
			return (true);
			break;
		case No:
			return (false);
			break;
		default:
			UnknownCommand();
			choice = 0;
			break;
		}
	}
	return (true);
}