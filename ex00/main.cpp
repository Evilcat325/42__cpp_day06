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
	well treating 0 as 0 '0' as char for now...
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
	if (!isnan(number) && !isinf(number) && floor(number) == number)
		std::cout << ".0";
	std::cout << "f" << std::endl;

	// append .0 if whole number
	std::cout << "double: " << number;
	if (!isnan(number) && !isinf(number) && floor(number) == number)
		std::cout << ".0";
	std::cout << std::endl;

	exit(0);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "expecting one and only one parameter" << std::endl;
		return 0;
	}
	std::string input = argv[1];

	// implict promotion char to double
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'')
		print_double(input[1]);
	int i;
	double d;
	std::istringstream sin(input);
	// implict promotion int to double
	if (input.find('.') == std::string::npos && (sin >> i))
		print_double(i);

	sin.clear();
	sin.str(input);
	// check double literal first (default to double)
	if (!(sin >> d))
	{
		// failed but could be a floot literal
		if (input[input.length() - 1] == 'f')
			input = input.substr(0, input.length() - 1);
		std::istringstream sinnof(input);
		if (!(sinnof >> d))
			print_error();
	}

	print_double(d);
	return 0;
}
