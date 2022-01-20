#pragma once

#include "U_string.h"

U_string::U_string()
{
	this->str = nullptr;
	this->lenght = 0;
	this->capacity = 0;

	return;
}

U_string::U_string(const wchar_t* _str)
{
	this->lenght = wcslen(_str);
	this->capacity = this->lenght;
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
	this->capacity = this->lenght;
	this->str = new wchar_t[this->lenght];

	for (int i = 0; i < this->lenght; ++i)
	{
		this->str[i] = _str.str[i];
	}

	return;
}

size_t U_string::get_lenght() const
{
	return this->lenght;
}

size_t U_string::get_capacity() const
{
	return this->capacity;
}

void U_string::clear()
{
	delete[] this->str;
	this->str = nullptr;

	this->capacity = 0;
	this->lenght = 0;

	return;
}

void U_string::push(const wchar_t& elem)
{
	if (this->capacity <= this->lenght)
	{
		this->_change_size(8);
	}

	this->str[this->lenght] = elem;
	++this->lenght;

	return;
}

void U_string::increase(const U_string& _data, int position)
{
	if (position < 1 || position>this->lenght + 1) throw "Error position in 'increase'";

	--position;

	if (this->capacity < this->lenght + _data.lenght)
	{
		this->_change_size(this->lenght + _data.lenght + 8);
	}

	for (int i = this->lenght + _data.lenght - 1; i >= position + _data.lenght; --i)
	{
		this->str[i] = this->str[i - _data.lenght];
	}

	int index_data = _data.lenght - 1;
	for (int i = position - 1 + _data.lenght; i >= position; --i)
	{
		this->str[i] = _data.str[index_data];
		--index_data;
	}

	this->lenght += _data.lenght;

	return;
}

void U_string::increase(const wchar_t* _data, const int position)
{

}

void U_string::increase(const wstring& _data, const int position)
{

}

void U_string::increase(const string& _data, const int position)
{

}

void U_string::increase(const char* _data, const int position)
{

}


wostream& operator<<(wostream& out, const U_string& u_str)
{
	for (int i = 0; i < u_str.lenght; ++i)
	{
		if (u_str.str[i] == '\0') break;	// must check
		out << u_str.str[i];
	}

	return out;
}

wistream& operator>>(wistream& in, U_string& u_str)
{
	u_str.clear();

	wchar_t temp;
	temp = in.get();

	while (temp!='\n')
	{
		u_str.push(temp);
		temp = in.get();
	}

	return in;
}

U_string::~U_string()
{
	delete[] this->str;

	return;
}

void U_string::_change_size(const size_t add)
{
	size_t add_size = add < 5 ? 5 : add;
	wchar_t* new_str = new wchar_t[this->lenght + add_size];

	for (int i = 0; i < this->lenght; ++i)
	{
		new_str[i] = this->str[i];
	}
	if (this->str != nullptr) delete[] this->str;

	this->str = new_str;
	this->capacity = this->lenght + add_size;
	new_str = nullptr;

	for (int i = this->lenght; i < this->capacity; ++i)
	{
		this->str[i] = '\0';
	}

	return;
}