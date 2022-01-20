#pragma once

#include <iostream>
#include <string>

using namespace std;

class U_string
{
public:
	U_string();
	U_string(const wchar_t* _str);
	U_string(const wstring& _str);
	U_string(const string& _str);
	U_string(const char* _str);
	U_string(const U_string& _str);
	
	size_t get_lenght() const;

	size_t get_capacity() const;
	
	void clear();
	void push(const wchar_t& elem);

	friend wostream& operator<<(wostream& out, const U_string& u_str);
	friend wistream& operator>>(wistream& in, U_string& u_str);

	~U_string();

private:
	wchar_t* str;
	size_t lenght;
	size_t capacity;

	void _change_size(const size_t add);
};