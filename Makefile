CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98
EXEC = ft_containers
SRC_DIR = srcs
OBJ_DIR = srcs/objs
INC_DIR = includes

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re
