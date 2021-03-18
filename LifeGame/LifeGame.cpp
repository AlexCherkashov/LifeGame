#include <iostream>
#include <windows.h>
#include "CinClear.h"
#include "FromConsole.h"
#include "FromFile.h"
#include "Main.h"
#include "UnknownCommand.h"
#include "RandomInput.h"
#include <vector>
#include <cmath>
#include <conio.h>
#include <set>

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Программа имитирует жизнь колонии клеток." << endl
        << "Автор Черкашов Александр, 474 группа" << endl << endl
		<< "Для отрисовки на каждом шаге нажимайте пробел" << endl
		<< "Если вы хотите закончить отрисовку, нажмите ESC" << endl << endl;
	RunProgram();
}

void RunProgram() {
	int choice = 1;
	while (true) {
		cout << "1 - Запуск программы\n"
			<< "2 - Выход из программы" << endl;
		cin >> choice;
		cout << endl;
		CinClear();

		switch (choice)
		{
		case Run::Life:
			BeginOfProcess();
			system("cls");
			break;
		case Run::Exit:
			return;
		default:
			UnknownCommand();
		}
	}
}

void BeginOfProcess() {
	int choice{};
	while (true) {
		cout << "Выберите сповоб ввода данных\n" << "1 - Ввод с консоли\n"
			<< "2 - Ввод из файла\n3 - Случайные значения" << endl;
		cin >> choice;
		cout << endl;
		CinClear();

		switch (choice)
		{
		case InputFromConsole:
			FromConsole();
			return;
			break;
		case InputFromFile:
			FromFile();
			return;
		case InputRandom:
			RandomInput();
			return;
		default:
			UnknownCommand();
		}
	}
}