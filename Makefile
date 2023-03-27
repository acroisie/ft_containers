CC			:= c++
CC_FLAGS	:= -Wall -Werror -Wextra -std=c++98 #-fsanitize=address
NAME		:= ft_containers
OBJS_DIR 	:= srcs/objs/
SRCS_DIR	:= srcs/
SOURCES		:= $(wildcard $(SRCS_DIR)*.cpp)
OBJECTS		:= $(SOURCES:$(SRCS_DIR)%.cpp=$(OBJS_DIR)%.o)
INC_DIR		:= includes/
INCLUDES	:= $(wildcard $(INC_DIR)*.hpp)

all: $(NAME)
$(NAME): $(OBJS_DIR) $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(CC_FLAGS)

$(OBJS_DIR):
	@mkdir -p $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp $(INCLUDES) Makefile | $(OBJS_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re