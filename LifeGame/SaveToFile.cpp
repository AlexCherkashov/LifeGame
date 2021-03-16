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
		cout << "������� ����� ����� � ������� .txt:" << endl;
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
				cout << "���� ������ ��� ������, �������� ������ ����" << endl;
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
	cout << "������ ������� ���������" << endl;
}

bool IsContinueToSave() {
	int choice;
	while (true) {
		cout << "����� ���� ��� ����, ������������?" << endl
			<< "1 - ��\n2 - ���" << endl;
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
	cout << "������ ��������� �������� ������?" << endl
		<< "1 - ��\n2 - ���" << endl;
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