FLAGS = -Wall -Wextra -Werror
STD = -std=c++98
CC = clang++
SOURCES = *.cpp
NAME = main

$(NAME): $(SOURCES)
	$(CC) $(FLAGS) $(STD) $(SOURCES) -o $(NAME) -g

test: $(NAME)
	@./$(NAME)

diff: test
	diff -U 3 $(NAME).output test.output

clean:
	rm -f $(NAME)

re : clean $(NAME)
