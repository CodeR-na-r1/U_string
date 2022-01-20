#pragma once

#include <iostream>
#include <vector>
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

	void increase(const U_string& _data, const int position);
	void increase(const wchar_t* _data, const int position);
	void increase(const wstring& _data, const int position);
	void increase(const string& _data, const int position);
	void increase(const char* _data, const int position);

	void push_back(const U_string& _data);
	void push_back(const wchar_t* _data);
	void push_back(const wstring& _data);
	void push_back(const string& _data);
	void push_back(const char* _data);

	U_string cut(int _begin, int _end) const;
	
	vector<U_string> split(const U_string& separator, const int max_count_cut = 0) const;

	vector<U_string> find(const U_string& mask_template, const int max_count_elem = -1) const;

	U_string& operator=(const U_string& u_str);
	U_string& operator=(const wchar_t* u_str);
	U_string& operator=(const wstring& u_str);
	U_string& operator=(const string& u_str);
	U_string& operator=(const char* u_str);

	friend wostream& operator<<(wostream& out, const U_string& u_str);
	friend wistream& operator>>(wistream& in, U_string& u_str);

	~U_string();

private:
	wchar_t* str;
	size_t lenght;
	size_t capacity;

	void _change_size(const size_t add);
};