#pragma once

// This header is intended to enclose the methods for debug purposes.
// The intention is that the functions could be called throughout the project but the libraries it uses can be easily replaced.

// Prints a string to the console
void Debug_Print(const char* string);

// Prints a string to the console and ends the line
void Debug_PrintLine(const char* string);

// Ends the line in the console
void Debug_EndLine();