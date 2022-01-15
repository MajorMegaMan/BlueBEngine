#include "Debug.h"
#include <iostream>

void Debug_Print(const char* string)
{
	// ensure the char array is safe to use
	std::string toPrint(string);

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

void Debug_EndLine()
{
	std::cout << std::endl;
}