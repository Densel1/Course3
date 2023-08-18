
#include <iostream>
#include "ini_parser.h"

int main()
{
	ini_parser parser("filename.ini");
	auto value = parser.get_value("Section1.var1");
	std::cout << value << endl;
}
