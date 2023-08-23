
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "ini_parser.h"


void read_file(std::string name, std::multimap<std::string, std::pair<std::string, std::string>> &m)
{
	std::ifstream in(name);
	std::string line;
	bool is_reading_section = false;
	bool is_reading_value = false;
	std::string section_name;
	std::string value;
	std::string value_name;

	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			//				cout << "line " << line << endl;
			for (auto& s : line)
			{
				if (s == ';') break;
				if (s == '[')
				{
					if (!section_name.empty())
						section_name.erase();
					is_reading_section = true;
					continue;
				}
				if (s == ']')
				{
					is_reading_section = false;
					continue;
				}
				if (s == '=')
				{
					is_reading_value = true;
					continue;
				}

				if (is_reading_section)
					section_name.push_back(s);
				else if (is_reading_value)
				{
					value.push_back(s);
				}
				else value_name.push_back(s);
			}


			if (is_reading_value && !value.empty())
			{

			//	std::cout << value << std::endl;

				std::pair<std::string, std::string> p1(value_name, value);

				m.insert(std::pair<std::string, std::pair<std::string, std::string>>(section_name, p1));

				value.erase();
			}
			is_reading_value = false;
			value_name.erase();
		}
	}
	else  throw std::exception("can't open file"); //std::cout << "can't open file" << std::endl; }
	in.close();
}  



int main()
{
	try{
    std::multimap<std::string, std::pair<std::string, std::string>> m;
	read_file("filename.ini", m);
	ini_parser parser(m);
	auto value = parser.get_value<int>("Section1.var2");
    std::cout << "VALUE = " << value << std::endl;
	}
	catch (const std::exception& ex) { std::cout << ex.what() << std::endl; };
//	catch (...) { std::cout << "unknown error"; }
	return 0;
}
