NAME = PmergeMe
CC = c++
FLAGS = -std=c++98 -Wall -Werror -Wextra

HEADERS = PmergeMe.hpp

SRC = main.cpp \
	  PmergeMe.cpp

OBJ = main.o \
	  PmergeMe.o

all:$(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ)

fclean: clean 
	$(RM) $(NAME)

re: clean all

.PHONY:all clean fclean re
