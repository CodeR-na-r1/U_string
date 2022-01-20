#include <iostream>

#include "U_string.h"

using namespace std;

int main()
{
	const char* s = "ggg";
	U_string str=s;
	wcout << str << endl;
	wcin >> str;
	wcout << str << endl;
	wcout << str.get_lenght() << endl;
	U_string str_2 = "cat";
	U_string str_3 = "X";
	str_2.increase(str_3, 4);
	wcout << str_2 << endl;

	U_string str_4 = "RUSSI";
	str_4.push_back("A");
	wcout << str_4 << endl;

	U_string separator("S");
	vector<U_string> elements;
	elements = str_4.split(separator);
	for (int i = 0; i < elements.size(); i++)
	{
		wcout << i + 1 << " element = " << elements[i] << endl;
	}

	return 0;
}