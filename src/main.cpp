#include "../include/Printf.h"
#include <iostream>

int main()
{
	char buffer[1024];
	char tinyBuffer[10];

	unsigned int test = 42;

	//testing
	Printf(buffer, buffer + 1023, "Forty Two %d %u %c %s %x %b %%", -42, test, '*', "Forty Two", 42, 42);
	std::cout << buffer << "\n";

	Printf(tinyBuffer, tinyBuffer + 9, "A String That is too long for the buffer");
	std::cout << tinyBuffer << "\n";

	Printf(buffer, buffer + 1023, "%w %%%");
	std::cout << buffer << "\n";

	Printf(buffer, buffer + 1023, "");
	std::cout << buffer << "\n";
}