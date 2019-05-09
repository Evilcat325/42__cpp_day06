
#include <string>
#include <cstdlib>
#include <iostream>

struct Data
{
	std::string s1;
	int n;
	std::string s2;
};

void fill_random_8_string(char *s)
{
	static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < 8; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
}

void *serialize(void)
{
	void *raw = new char[(sizeof(char) * 16 + sizeof(int)) / (sizeof(char))];
	char *s1 = reinterpret_cast<char *>(raw);
	fill_random_8_string(s1);
	int *as_int = reinterpret_cast<int *>(s1 + 8);
	*as_int = rand();
	as_int++;
	fill_random_8_string(reinterpret_cast<char *>(as_int));
	return raw;
}

Data *deserialized(void *raw)
{
	char *s1 = reinterpret_cast<char *>(raw);
	char *s2 = s1 + 8 + sizeof(int) / sizeof(char);
	Data *data = new Data;
	data->s1 = std::string(s1, 8);
	data->s2 = std::string(s2, 8);
	data->n = *reinterpret_cast<int *>(s1 + 8);
	return data;
}

int main()
{
	srand(time(NULL));
	void *raw_data = serialize();
	Data *data = deserialized(raw_data);
	std::cout << data->s1 << std::endl;
	std::cout << data->n << std::endl;
	std::cout << data->s2 << std::endl;
	return 0;
}
