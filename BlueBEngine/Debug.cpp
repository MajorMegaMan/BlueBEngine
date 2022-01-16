#include "Debug.h"
#include <iostream>
#include <sstream>
#include <string>

void Debug_Print(const char* string)
{
	// ensure the char array is safe to use
	std::string toPrint(string);

	// print to console
	std::cout << toPrint;
}

void Debug_Print(int value)
{
	// ensure the char array is safe to use
	std::string toPrint = std::to_string(value);

	// print to console
	std::cout << toPrint;
}

void Debug_PrintLine(const char* string)
{
	// ensure the char array is safe to use
	std::string toPrint(string);

	// print to console
	std::cout << toPrint << std::endl;
}

void Debug_PrintLine(int value)
{
	// ensure the char array is safe to use
	std::string toPrint = std::to_string(value);

	// print to console
	std::cout << toPrint << std::endl;
}

void Debug_EndLine()
{
	std::cout << std::endl;
}
