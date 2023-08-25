
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "myException.h"
#include "ini_parser.h"



void read_file(std::string name, std::multimap<std::string, std::pair<std::string, std::string>> &m)
{
	std::ifstream in(name);
	std::string line;
	bool is_reading_section = false;
	bool is_reading_value = false;
	bool delete_spases = true;
	std::string section_name;
	std::string value;
	std::string value_name;
	unsigned string_number = 0;
	bool first_section = 0;

	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			string_number++;
			for (auto& s : line)
			{
				if (s == ';') break;
				if (s == '[')
				{
					if (!section_name.empty())
						section_name.erase();
					if (is_reading_section)
					{
						throw myException("duplicate bracket in line:", string_number);
					}
					if (!is_reading_value) is_reading_section = true;
					continue;
				}
				if (s == ']')
				{
					if (is_reading_section)
					{
						is_reading_section = false;
						first_section = true;
						continue;
					}
					else throw myException("wrong symbol at line:", string_number);
				}
				if (s == '=')
				{
					is_reading_value = true;
					continue;
				}
				if (s == ' ')
				{
					if (delete_spases) continue;
				}
				if (s != ' ')
				{
					if (is_reading_value&&delete_spases) {
						delete_spases = false;
					}
				}
				if (is_reading_section)
					section_name.push_back(s);
				else if (is_reading_value)
				{
					if(!delete_spases) value.push_back(s);
				}
				else
				{
					if (first_section)
					{
						if (s != ' ') value_name.push_back(s);
					}
					else throw myException("no section for value in line: ", string_number);
				}
			}


			if (is_reading_value && !value.empty())
			{
				std::pair<std::string, std::string> p1(value_name, value);
				m.insert(std::pair<std::string, std::pair<std::string, std::string>>(section_name, p1));
				value.erase();
			}
			is_reading_value = false;
			delete_spases = true;
			value_name.erase();
		}
	}
	else  throw myException("can't open file");
	in.close();
}  



int main()
{
	try{
    std::multimap<std::string, std::pair<std::string, std::string>> m;
	read_file("filename.ini", m);
	ini_parser parser(m);
	auto value = parser.get_value<int>("Section1.var1");
    std::cout << "VALUE = " << value << std::endl;
	auto value1 = parser.get_value<std::string>("Section1.var2");
	std::cout << "VALUE1 = " << value1 << std::endl;
	auto value2 = parser.get_value<int>("Section2.var1");
	std::cout << "VALUE2 = " << value2 << std::endl;
	auto value3 = parser.get_value<std::string>("Section2.var2");
	std::cout << "VALUE3 = " << value3 << std::endl;
	auto value4 = parser.get_value<std::string>("Section1.var1");
	std::cout << "VALUE4 = " << value4 << std::endl;
	auto value5 = parser.get_value<std::string>("Section2.val1");
	std::cout << "VALUE5 = " << value5 << std::endl;
	}
	catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
	catch (...) { std::cout << "unknown error" << std::endl; }
	return 0;
}
