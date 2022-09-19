CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -fsanitize=address -Ofast

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = ft_containers

TEST_VECTOR	= test_vector
TEST_VECTOR_PERFORMANCE	= test_vector_perf
TEST_MAP = test_map
TEST_MAP_PERFORMANCE = test_map_perf
TEST_STACK = test_stack
TEST_STACK_PERFORMANCE	= test_stack_perf

all : $(NAME);

$(NAME) : $(OBJS)
	@echo "Creating $(NAME)"
	@$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_VECTOR): ./tests/$(TEST_VECTOR).cpp
	@$(CXX) $(CXXFLAGS) -o $(TEST_VECTOR) ./tests/$(TEST_VECTOR).cpp -I.
	@./$(TEST_VECTOR) > ft_output;
	@$(CXX) $(CXXFLAGS) -o $(TEST_VECTOR) -D USE_STD ./tests/$(TEST_VECTOR).cpp -I.
	@./$(TEST_VECTOR) > std_output;
	@diff ft_output std_output -s
	@$(RM) ft_output std_output;
	@$(RM) $(TEST_VECTOR);

$(TEST_VECTOR_PERFORMANCE): ./tests/$(TEST_VECTOR_PERFORMANCE).cpp
	@$(CXX) $(CXXFLAGS) -o $(TEST_VECTOR_PERFORMANCE) ./tests/$(TEST_VECTOR_PERFORMANCE).cpp -I.
	@./$(TEST_VECTOR_PERFORMANCE)
	@$(RM) $(TEST_VECTOR_PERFORMANCE);

$(TEST_MAP): ./tests/$(TEST_MAP).cpp
	@$(CXX) $(CXXFLAGS) -o $(TEST_MAP) ./tests/$(TEST_MAP).cpp -I.
	@./$(TEST_MAP) > ft_output;
	@$(CXX) $(CXXFLAGS) -o $(TEST_MAP) -D USE_STD ./tests/$(TEST_MAP).cpp -I.
	@./$(TEST_MAP) > std_output;
	@diff ft_output std_output -s
	@$(RM) ft_output std_output;
	@$(RM) $(TEST_MAP);

$(TEST_MAP_PERFORMANCE): ./tests/$(TEST_MAP_PERFORMANCE).cpp
	@$(CXX) $(CXXFLAGS) -o $(TEST_MAP_PERFORMANCE) ./tests/$(TEST_MAP_PERFORMANCE).cpp -I.
	@./$(TEST_MAP_PERFORMANCE)
	@$(RM) $(TEST_MAP_PERFORMANCE);

$(TEST_STACK): ./tests/$(TEST_STACK).cpp
	@$(CXX) $(CXXFLAGS) -o $(TEST_STACK) ./tests/$(TEST_STACK).cpp -I.
	@./$(TEST_STACK) > ft_output;
	@$(CXX) $(CXXFLAGS) -o $(TEST_STACK) -D USE_STD ./tests/$(TEST_STACK).cpp -I.
	@./$(TEST_STACK) > std_output;
	@diff ft_output std_output -s
	@$(RM) ft_output std_output;
	@$(RM) $(TEST_STACK);

$(TEST_STACK_PERFORMANCE): ./tests/$(TEST_STACK_PERFORMANCE).cpp
	@$(CXX) $(CXXFLAGS) -o $(TEST_STACK_PERFORMANCE) ./tests/$(TEST_STACK_PERFORMANCE).cpp -I.
	@./$(TEST_STACK_PERFORMANCE)
	@$(RM) $(TEST_STACK_PERFORMANCE);

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
