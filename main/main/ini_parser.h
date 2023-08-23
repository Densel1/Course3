#pragma once
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <iostream>



class ini_parser
{
private:
	std::multimap<std::string, std::pair<std::string, std::string>> sections;

public:
	ini_parser() = delete;
	ini_parser(const std::multimap<std::string, std::pair<std::string, std::string>>& m)
	{
		sections = std::move(m);
		//for (auto it = begin(sections); it != end(sections); ++it)
		//{
		//	std::cout << it->first << std::endl;
		//	std::cout << it->second.first << std::endl;
		//	std::cout << it->second.second << std::endl;
		//}

	};

	template <typename T>
	T get_value(const std::string& line);

	~ini_parser() = default;

private:


	bool is_number(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && (std::isdigit(*it) || (*it == '.'))) { 	++it;
		}
		it++;
		return !s.empty() && it == s.end();
	}
};

