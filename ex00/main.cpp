#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>

/*
	atof out of range return undefined, no conversion return 0
	strtod is in C99 not part of C++98
	stod is in C++1
	using stringstream but it treats optional suffix f L as error....
	so adding a few manual checking
	only doing decimal int, decimal float..
	stupid pdf:
	char literal : '0' - '9' collpas with int literal
	treating then as ambiguous literal will print both result
*/

void print_error()
{
	std::cerr << "char: impossible" << std::endl
						<< "int: impossible" << std::endl
						<< "float: impossible" << std::endl
						<< "double: impossible" << std::endl;
	exit(0);
}

void print_double(double number)
{
	// static cast then check number range to print according
	// cannot dynamic cast on scalar type
	char c = static_cast<char>(number);
	std::cout << "char: ";
	if (CHAR_MIN <= number && number <= CHAR_MAX)
		if (isprint(c))
			std::cout << c;
		else
			std::cout << "Non displayable";
	else
		std::cout << "impossible";
	std::cout << std::endl;
	// static cast then check number range to print according
	// cannot dynamic cast on scalar type
	std::cout << "int: ";
	if (INT_MIN <= number && number <= INT_MAX)
		std::cout << static_cast<int>(number);
	else
		std::cout << "impossible";
	std::cout << std::endl;
	// static cat only lose precision
	// still able to represent -inf +inf nan
	// added f suffix per pdf output
	std::cout << "float: " << static_cast<float>(number);
	if (floor(number) == number)
		std::cout << ".0";
	std::cout << "f" << std::endl;

	// append .0 if whole number
	std::cout << "double: " << number;
	if (floor(number) == number)
		std::cout << ".0";
	std::cout << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "expecting one and only one parameter" << std::endl;
		return 0;
	}
	std::string input = argv[1];
	//removing suffix f as double have more precision to float;

	double d;
	if (input.length() == 1)
	{
		char c;
		std::istringstream sinchar(input);
		if (!(sinchar >> c))
			print_error();
		d = c;
		if (isnumber(c))
		{
			std::cout << "Printing as int literal" << std::endl;
			print_double(d - '0');
			std::cout << "Printing as char literal" << std::endl;
		}
		print_double(d);
	}
	else
	{
		std::istringstream sin(input);
		if (!(sin >> d))
		{
			if (input[input.length() - 1] == 'f')
				input = input.substr(0, input.length() - 1);
			std::istringstream sinnof(input);
			if (!(sinnof >> d))
				print_error();
		}
		print_double(d);
	}
	return 0;
}
