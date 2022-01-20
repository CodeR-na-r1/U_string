#pragma once

#include <string>

using namespace std;

class U_string
{
private:
	wchar_t* str;
	size_t lenght;

public:
	U_string();
	U_string(const wchar_t* _str);
	U_string(const wstring& _str);
	U_string(const string& _str);
	U_string(const char* _str);
	U_string(const U_string& _str);
	





	friend wostream& operator<<(wostream& out, const U_string& u_str);
	friend wistream& operator>>(const wistream& in, const U_string& u_str);

	~U_string();
};