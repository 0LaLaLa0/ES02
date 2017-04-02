#include <iostream>
char _hex[] = {'0', '1', '2'};
int main()
{
	int i = 0;
	std::cout << _hex[i++] << std::endl;
	i = 0;
	std::cout << _hex[++i] << std::endl;
	return 0;
}