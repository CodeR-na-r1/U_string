#pragma once

#include "U_string.h"
#include <codecvt>

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
	this->increase(U_string(_data), position);

	return;
}

void U_string::increase(const wstring& _data, const int position)
{
	this->increase(U_string(_data), position);

	return;
}

void U_string::increase(const string& _data, const int position)
{
	this->increase(U_string(_data), position);

	return;
}

void U_string::increase(const char* _data, const int position)
{
	this->increase(U_string(_data), position);

	return;
}

void U_string::push_back(const U_string& _data)
{
	this->increase(_data, this->lenght + 1);

	return;
}

void U_string::push_back(const wchar_t* _data)
{
	this->increase(_data, this->lenght + 1);

	return;
}

void U_string::push_back(const wstring& _data)
{
	this->increase(_data, this->lenght + 1);

	return;
}

void U_string::push_back(const string& _data)
{
	this->increase(_data, this->lenght + 1);

	return;
}

void U_string::push_back(const char* _data)
{
	this->increase(_data, this->lenght + 1);

	return;
}

U_string U_string::cut(int _begin, int _end) const
{
	if (_begin < 0 || _begin > _end || _end > this->lenght)
	{
		throw "Error arguments in 'cut'";
	}

	U_string res;

	for (int i = _begin; i < _end; ++i)
	{
		res.push(this->str[i]);
	}

	return res;
}

vector<U_string> U_string::split(const U_string& separator, const int max_count_parts) const
{
	if (separator.lenght > this->lenght || separator.lenght == 0)
	{
		throw "Error arguments in 'split'";
	}

	vector<U_string> res;

	int count_parts(1);
	int from(0);
	for (int i = 0; i < this->lenght; ++i)
	{
		if (this->str[i] != separator.str[0])
		{
			continue;
		}
		else
		{
			if (this->lenght - i < separator.lenght)
			{
				break;
			}
			bool copmpare = true;
			for (int j = 1; j < separator.lenght; j++)
			{
				if (this->str[i + j] != separator.str[j])
				{
					copmpare = false;
					break;
				}
			}
			if (copmpare)
			{
				if (from == i) continue;
				res.push_back(this->cut(from, i));
				++count_parts;
				if (count_parts == max_count_parts) break;
				from = i + separator.lenght;
			}
		}
	}

	if (from < this->lenght)
		res.push_back(this->cut(from, this->lenght));
	
	return res;
}

vector<U_string> U_string::find(const U_string& mask_template, const int max_count_elem) const
{
	if (mask_template.lenght > this->lenght || mask_template.lenght == 0)
	{
		throw "Error arguments in 'find'";
	}

	vector<U_string> res;

	int now_index_mask(0);
	int from(0);
	int count_elems(0);
	bool star = false;
	
	for (int i = 0; i < this->lenght; ++i)
	{
		if (now_index_mask == mask_template.lenght) { res.push_back(this->cut(from, i)); i = ++from; now_index_mask = 0; ++count_elems; if (count_elems == max_count_elem) { break; } }
		if (mask_template.str[now_index_mask] == '?') { ++now_index_mask; continue; }	// Маска, допускающая наличие любого количества произвольных символов
		if (mask_template.str[now_index_mask] == '*') { star = true; --i; ++now_index_mask; continue; }	// Маска, допускающая наличие любого количества цифры
		if (mask_template.str[now_index_mask] == '#')	// Маска, допускающая наличие любой цифры
		{
			if (this->str[i] - L'0' >= 0 && this->str[i] - L'0' <= 9) { ++now_index_mask; continue; }
			now_index_mask = 0;
			i = ++from - 1;
		}
		if (star)
		{
			if (this->str[i] == mask_template.str[now_index_mask]) { star = false; ++now_index_mask; }
			continue;
		}
		if (!star)
		{
			if (this->str[i] == mask_template.str[now_index_mask]) { ++now_index_mask; continue; }
			now_index_mask = 0;
			i = ++from - 1;
		}
	}

	if (now_index_mask == mask_template.lenght)
	{
		res.push_back(this->cut(from, this->lenght));
	}

	return res;
}

void U_string::get_statistics() const
{
	vector<U_string> elements;
	U_string separator;

	wcout << L"--- Statistics for the line: ---" << endl << *this << endl;

	separator = ".";
	elements = this->split(separator);
	wcout << L"Number of proposals: " << elements.size() << endl;
	elements.clear();

	separator = " ";
	elements = this->split(separator);
	wcout << L"Number of words: " << elements.size() << endl;
	elements.clear();
	
	wcout << L"Number of characters: " << this->lenght << endl;

	return;
}

int U_string::get_amount_given_word(const U_string& u_str) const
{
	vector<U_string> res = this->find(u_str);

	return res.size();
}

int U_string::get_amount_prepositions() const
{
	set<U_string> contain;
	wifstream in(L"prepositions.txt");
	in.imbue(std::locale(in.getloc(), new std::codecvt_utf16<wchar_t, 1114111UL, std::little_endian>));

	if (!in.is_open())
	{
		wcout << L"File opening error!" << endl;
		return 0;
	}

	U_string temp;

	this->get_line(in, temp);

	while (temp.lenght)
	{
		wcout << temp << endl;
		contain.insert(temp);
		this->get_line(in, temp);
	}
	in.close();

	wcout << L"Предлоги:" << endl;
	for (auto it = contain.begin(); it != contain.end(); ++it)
	{
		wcout << *it << endl;
	}

	return 0;
}

U_string& U_string::operator=(const U_string& u_str)
{
	if (this->capacity < u_str.lenght)
	{
		this->_change_size(u_str.lenght + 8);
	}

	for (int i = 0; i < u_str.lenght; ++i)
	{
		this->str[i] = u_str.str[i];
	}

	this->lenght = u_str.lenght;

	return *this;
}

U_string& U_string::operator=(const wchar_t* u_str)
{
	this->operator=(U_string(u_str));

	return *this;
}

U_string& U_string::operator=(const wstring& u_str)
{
	this->operator=(U_string(u_str));

	return *this;
}

U_string& U_string::operator=(const string& u_str)
{
	this->operator=(U_string(u_str));

	return *this;
}

U_string& U_string::operator=(const char* u_str)
{
	this->operator=(U_string(u_str));

	return *this;
}

bool U_string::operator==(const U_string& u_str) const
{
	if (this->lenght != u_str.lenght)
		return false;

	for (int i = 0; i < this->lenght; ++i)
	{
		if (this->str[i] != u_str.str[i])
			return  false;
	}

	return true;
}

bool U_string::operator!=(const U_string& u_str) const
{
	return !this->operator==(u_str);
}

bool U_string::operator>(const U_string& u_str) const
{
	if (this->lenght > u_str.lenght)
	{
		return true;
	}

	if (this->lenght < u_str.lenght)
	{
		return false;
	}

	for (int i = 0; i < this->lenght; ++i)
	{
		if (this->str[i] > u_str.str[i])
			return true;
		else if (this->str[i] < u_str.str[i])
			return false;
		else
			continue;
	}

	return false;
}

bool U_string::operator>=(const U_string& u_str) const
{
	if (this->lenght > u_str.lenght)
	{
		return true;
	}

	if (this->lenght < u_str.lenght)
	{
		return false;
	}

	for (int i = 0; i < this->lenght; ++i)
	{
		if (this->str[i] >= u_str.str[i])
			return true;
		else if (this->str[i] < u_str.str[i])
			return false;
		else
			continue;
	}

	return true;
}

bool U_string::operator<(const U_string& u_str) const
{
	return !this->operator>(u_str);
}

bool U_string::operator<=(const U_string& u_str) const
{
	return !this->operator>=(u_str);
}

wostream& operator<<(wostream& out, const U_string& u_str)
{
	for (int i = 0; i < u_str.lenght; ++i)
	{
		if (u_str.str[i] == '\0') break;
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

void U_string::get_line(wifstream& in, U_string& u_str) const
{
	u_str.clear();

	wchar_t temp;
	in >> temp;
	wcout << temp << endl;

	while (temp != L'\n' && !in.eof())
	{
		u_str.push(temp);
		wcout << u_str << endl;
		in >> temp;
	}

	return;
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