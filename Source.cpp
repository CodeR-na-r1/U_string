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
	str_2.increase(str_3, 5);
	wcout << str_2 << endl;
	return 0;
}