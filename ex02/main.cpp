#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <exception>
#include <iostream>
#include <cstdlib>
#include <ctime>

Base *generate(void)
{
	Base *ptr;
	int abc = rand() % 3;
	if (abc == 0)
		ptr = new A();
	else if (abc == 1)
		ptr = new B();
	else
		ptr = new C();
	return ptr;
}
//(void) tell compiler it does nothing, not a cast..
// & throw * don't so using & here
void identify_from_reference(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch (std::bad_cast &e)
	{
		std::cerr << "Not A " << e.what() << std::endl;
	}
	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch (std::bad_cast &e)
	{
		std::cerr << "Not B " << e.what() << std::endl;
	}
	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch (std::bad_cast &e)
	{
		std::cerr << "Not C " << e.what() << std::endl;
	}
}

void identify_from_pointer(Base *p)
{
	if (p == NULL)
	{
		std::cerr << "Null pointer" << std::endl;
		return;
	}
	// guess I will do it properly to show I know it wont throw and return null;

	A *a = dynamic_cast<A *>(p);
	if (a)
	{
		std::cout << "A" << std::endl;
		return;
	}
	else
		std::cerr << "Not A dynamic cast return NULL" << std::endl;
	B *b = dynamic_cast<B *>(p);
	if (b)
	{
		std::cout << "B" << std::endl;
		return;
	}
	else
		std::cerr << "Not B dynamic cast return NULL" << std::endl;
	C *c = dynamic_cast<C *>(p);
	if (c)
	{
		std::cout << "C" << std::endl;
		return;
	}
	else
		std::cerr << "Not C dynamic cast return NULL" << std::endl;
}
int main()
{
	srand(time(NULL));
	Base *random = generate();
	Base &randomRef = *random;
	identify_from_pointer(random);
	identify_from_reference(randomRef);
	return 0;
}
