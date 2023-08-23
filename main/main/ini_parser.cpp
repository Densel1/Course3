#include "ini_parser.h"



template <typename T>
T ini_parser::get_value(const std::string &line)
{
	//for (auto it = begin(sections); it != end(sections); ++it)
	//{
	//	std::cout << it->first << std::endl;
	//	std::cout << it->second.first << std::endl;
	//	std::cout << it->second.second << std::endl;
	//}

	std::string sectoin_name;
	std::string str = "";

	bool point_char = false;
	//section
	std::string sel;
	//value
	std::string val;
	for (auto& s : line)
	{
		if (s == '.') {
			point_char = true;
			continue;
		}
		if (!point_char)
		{
			sel.push_back(s);
		}
		else { val.push_back(s); }

	}
	//		std::cout << sel << std::endl;
	//		std::cout << val << std::endl;
	//		std::multimap<std::string, std::pair<std::string, std::string>>::iterator it = begin(sections);
	for (auto it = begin(sections); it != end(sections); it++)
	{
		//			std::cout << "noop" << std::endl;
		if ((it->first) == sel)
		{
			//				std::cout << sel << std::endl;
			if (val == (it->second.first))
			{
				//					std::cout << "read " << val << std::endl;
				str = it->second.second;
				//					std::cout << str << std::endl;
			}
			//				else std::cout << val << " != " << it->second.first << std::endl;
		}
		// this works in C++17
	}
	if (str == "") throw std::exception("empty data");
	if constexpr (std::is_same_v<T, std::string>) return str;
	else if constexpr (std::is_same_v<T, int>)
	{
		if (is_number(str)) return atoi(str.c_str());
		else throw std::exception("not a number");
	}
}
