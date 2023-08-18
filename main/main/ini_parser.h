#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;


class ini_parser
{
private:
	std::multimap<std::string, pair<std::string,string>> sections;

public:
	ini_parser(std::string name) :fName(name)//, sections("","")
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
					std::pair<std::string, std::string> p1;
                    p1 = make_pair(value_name, value);

					sections.insert(pair<string, pair<string, string>>(section_name, p1));

					value.erase();
				}
				is_reading_value = false;
				value_name.erase();
			}
		}
	}

	std::string fName;


	//template <typename T>
	string get_value(std::string line)
	{
	 // T value;
	 // const type_info& ti = typeid(value);

	  string sectoin_name;
	  string str;
	  
	  bool point_char = false;
	  int i;
	  string sel;
	  string val;
	  for (auto& s : line)
	  {
	    if(s == '.'){
		  point_char = true;
		  continue;
		}
	    if(!point_char)
		{
			sel.push_back(s);
		}
		else { val.push_back(s); }
		
	  }
	  for(auto it = begin(sections); it!=end(sections);it++)
	  {
		if((it->first)==sel)
		{
		  if(str == (it->second.first))
		  {
			  {
				  cout << (it->second.first) << "=" << (it->second.second); // приводим значение my_value к типу возвращаемого параметра
			  }
		  }
		}
	  }
	  return " ";
	}
	

	template<typename T> void print_value(T value)
	{
		cout << "Value: " << static_cast<const char*>(&value) << std::endl;
	}


private:

	

	std::string read_string(std::string my_str)
	{
		std::string val;
		for (unsigned i = 0; i < my_str.length(); ++i)
		{
			if (my_str.at(i) == ';') break;
			if (my_str.at(i) == '=')
			{
			  for(int j = 0; (j!='\n')&&(j!=';');j++)
			  {
				  val.at(j) = my_str.at(j + i);
			  }
			}
		}
      return val;
	}

	bool is_number(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}
};

