#pragma once

#include "U_string.h"

U_string::U_string()
{
	this->str = nullptr;
	this->lenght = 0;

	return;
}

U_string::U_string(const wchar_t* _str)
{
	this->lenght = wcslen(_str);
	this->str = new wchar_t[this->lenght];

	for (int i = 0; i < this->lenght; ++i)
	{
		this->str[i] = _str[i];
	}

	return;
}

U_string::U_string(const wstring& _str) : U_string(_str.c_str())
{
	return;
}

U_string::U_string(const string& _str) : U_string(wstring(_str.begin(), _str.end()))
{
	return;
}

U_string::U_string(const char* _str) : U_string(string(_str))
{
	return;
}

U_string::U_string(const U_string& _str)
{
	this->lenght = _str.lenght;
	this->str = new wchar_t[this->lenght];

	for (int i = 0; i < this->lenght; ++i)
	{
		this->str[i] = _str.str[i];
	}

	return;
}

