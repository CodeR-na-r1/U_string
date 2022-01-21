#include <iostream>
#include <vector>
#include <clocale>
#include <io.h>
#include <fcntl.h>

#include "U_string.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	wcout << L"Работа конструкторов:" << endl;

	U_string example_1("example_1");

	const wchar_t* c_string = L"example_2";
	U_string example_2(c_string);

	string str("example_3");
	U_string example_3(str);

	wstring wide_character_string(L"example_4");
	U_string example_4(wide_character_string);

	U_string example_5(example_1);

	wcout << example_1 << " " << example_2 << " " << example_3 << " " << example_4 << " " << example_5 << " " << endl << endl;

	wcout << L"Поиск по заданному разделителю:" << endl;
	example_1 = "RUSSI";
	example_1.push_back("A");
	wcout << L"Поиск в строке: " << example_1 << endl;
	wcout << L"Разделитель: " << L"S" << endl;
	wcout << L"Результат:" << endl;
	vector<U_string> elements;
	elements = example_1.split(U_string("S"));
	for (int i = 0; i < elements.size(); i++)
	{
		wcout << i + 1 << L" element = " << elements[i] << endl;
	}

	wcout << endl << L"Поиск в строке: " << example_1 << endl;
	wcout << L"Разделитель: " << L"SS" << endl;
	wcout << L"Результат:" << endl;
	U_string separator("SS");
	elements.clear();
	elements = example_1.split(separator);
	for (int i = 0; i < elements.size(); i++)
	{
		wcout << i + 1 << L" element = " << elements[i] << endl;
	}
	wcout << endl;

	example_1 = "11wx wx";	//VCTTTK	//*T
	wcout << L"Поиск в строке подстроки, с возможностью поиска по маске (символы ? и *):" << endl;
	separator = "#wx";
	wcout << L"Строка: " << example_1 << L";\tШаблон (маска):" << separator << endl;
	elements.clear();
	elements = example_1.find(separator);
	for (int i = 0; i < elements.size(); i++)
	{
		wcout << i + 1 << L" element = " << elements[i] << endl;
	}

	wcout << endl;
	example_1 = L"РИЯ";
	wcout << L"Копирование в строку: " << example_1 << endl << L"Копируемая строка: " << L"ОСС" << endl;
	example_1.increase(L"ОСС", 2);
	wcout << L"Результат: " << example_1 << endl;

	wcout << endl;
	wcout << L"Копирование в конец строки: " << example_1 << endl << L"Копируемая строка: " << L"!!!" << endl;
	const wchar_t* temp = L"!!!";
	example_1.push_back(temp);
	wcout << L"Результат: " << example_1 << endl;

	example_1 = L"An arbitrary string for calculating word statistics and so on. Произвольная строка для подсчета статистики слов и тд.";
	wcout << endl << L"Получение статистики:" << endl;
	example_1.get_statistics();

	wcout << endl << L"Введите строку для проверки корректности ввода: " << endl;
	wcin >> example_1;
	wcout << endl << L"Вы ввели: " << example_1 << endl;

	wcout << endl << L"Проверка оператора сравнения (==) : " << endl;
	example_1 = L"Строка 1";
	example_2 = L"Строка 1";
	wcout << L"Строка 1: " << example_1 << L"\tСтрока 2: "<< example_2<< endl;
	wcout << L"Результат: " << (example_1 == example_2) << endl;

	wcout << endl << L"Проверка оператора неравенства (!=) : " << endl;
	example_1 = L"Строка 1";
	example_2 = L"Строка  1";
	wcout << L"Строка 1: " << example_1 << L"\tСтрока 2: " << example_2 << endl;
	wcout << L"Результат: " << (example_1 != example_2) << endl;

	wcout << endl << L"Подсчет определенного слова в строке: " << endl;
	example_1 = L"пр ппр ";
	example_2 = L"п";
	wcout << L"Строка поиска: " << example_1 << L"\tПодсчитываемое слово: " << example_2 << endl;
	wcout << L"Результат: " << example_1.get_amount_given_word(example_2) << endl;
	example_2 = L"пр";
	wcout << endl << L"Строка поиска: " << example_1 << L"\tПодсчитываемое слово: " << example_2 << endl;
	wcout << L"Результат: " << example_1.get_amount_given_word(example_2) << endl;

	return 0;
}