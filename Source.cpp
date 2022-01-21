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

	wcout << L"������ �������������:" << endl;

	U_string example_1("example_1");

	const wchar_t* c_string = L"example_2";
	U_string example_2(c_string);

	string str("example_3");
	U_string example_3(str);

	wstring wide_character_string(L"example_4");
	U_string example_4(wide_character_string);

	U_string example_5(example_1);

	wcout << example_1 << " " << example_2 << " " << example_3 << " " << example_4 << " " << example_5 << " " << endl << endl;

	wcout << L"����� �� ��������� �����������:" << endl;
	example_1 = "RUSSI";
	example_1.push_back("A");
	wcout << L"����� � ������: " << example_1 << endl;
	wcout << L"�����������: " << L"S" << endl;
	wcout << L"���������:" << endl;
	vector<U_string> elements;
	elements = example_1.split(U_string("S"));
	for (int i = 0; i < elements.size(); i++)
	{
		wcout << i + 1 << L" element = " << elements[i] << endl;
	}

	wcout << endl << L"����� � ������: " << example_1 << endl;
	wcout << L"�����������: " << L"SS" << endl;
	wcout << L"���������:" << endl;
	U_string separator("SS");
	elements.clear();
	elements = example_1.split(separator);
	for (int i = 0; i < elements.size(); i++)
	{
		wcout << i + 1 << L" element = " << elements[i] << endl;
	}
	wcout << endl;

	example_1 = "11wx wx";	//VCTTTK	//*T
	wcout << L"����� � ������ ���������, � ������������ ������ �� ����� (������� ? � *):" << endl;
	separator = "#wx";
	wcout << L"������: " << example_1 << L";\t������ (�����):" << separator << endl;
	elements.clear();
	elements = example_1.find(separator);
	for (int i = 0; i < elements.size(); i++)
	{
		wcout << i + 1 << L" element = " << elements[i] << endl;
	}

	wcout << endl;
	example_1 = L"���";
	wcout << L"����������� � ������: " << example_1 << endl << L"���������� ������: " << L"���" << endl;
	example_1.increase(L"���", 2);
	wcout << L"���������: " << example_1 << endl;

	wcout << endl;
	wcout << L"����������� � ����� ������: " << example_1 << endl << L"���������� ������: " << L"!!!" << endl;
	const wchar_t* temp = L"!!!";
	example_1.push_back(temp);
	wcout << L"���������: " << example_1 << endl;

	example_1 = L"An arbitrary string for calculating word statistics and so on. ������������ ������ ��� �������� ���������� ���� � ��.";
	wcout << endl << L"��������� ����������:" << endl;
	example_1.get_statistics();

	wcout << endl << L"������� ������ ��� �������� ������������ �����: " << endl;
	wcin >> example_1;
	wcout << endl << L"�� �����: " << example_1 << endl;

	wcout << endl << L"�������� ��������� ��������� (==) : " << endl;
	example_1 = L"������ 1";
	example_2 = L"������ 1";
	wcout << L"������ 1: " << example_1 << L"\t������ 2: "<< example_2<< endl;
	wcout << L"���������: " << (example_1 == example_2) << endl;

	wcout << endl << L"�������� ��������� ����������� (!=) : " << endl;
	example_1 = L"������ 1";
	example_2 = L"������  1";
	wcout << L"������ 1: " << example_1 << L"\t������ 2: " << example_2 << endl;
	wcout << L"���������: " << (example_1 != example_2) << endl;

	wcout << endl << L"������� ������������� ����� � ������: " << endl;
	example_1 = L"�� ��� ";
	example_2 = L"�";
	wcout << L"������ ������: " << example_1 << L"\t�������������� �����: " << example_2 << endl;
	wcout << L"���������: " << example_1.get_amount_given_word(example_2) << endl;
	example_2 = L"��";
	wcout << endl << L"������ ������: " << example_1 << L"\t�������������� �����: " << example_2 << endl;
	wcout << L"���������: " << example_1.get_amount_given_word(example_2) << endl;

	return 0;
}