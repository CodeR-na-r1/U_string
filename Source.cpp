#include <iostream>

#include "U_string.h"

using namespace std;

int main()
{
	const char* s = "ggg";
	U_string str=s;
	wcout << strlen(s) << endl;
	wcin >> str;
	wcout << str;
	return 0;
}