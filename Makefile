CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -fsanitize=address

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = ft_containers

all : $(NAME);

$(NAME) : $(OBJS)
	@echo "Creating $(NAME)"
	@$(CXX) $(CXXFLAGS) -o $@ $^

TEST_VECTOR	=	test_vector

$(TEST_VECTOR): ./test/$(TEST_VECTOR).cpp
	@$(CXX) $(CXXFLAGS) -o $(TEST_VECTOR) ./test/$(TEST_VECTOR).cpp -I.
	@./$(TEST_VECTOR) > ft_output;
	@$(CXX) $(CXXFLAGS) -o $(TEST_VECTOR) -D USE_STD ./test/$(TEST_VECTOR).cpp -I.
	@./$(TEST_VECTOR) > std_output;
	@diff ft_output std_output --report-identical-files;
	@$(RM) ft_output std_output;
	@$(RM) $(TEST_VECTOR);

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
