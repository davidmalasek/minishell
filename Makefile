# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Source files
SRC = src/main.c src/parse.c

# Output
NAME = minishell

# Library paths
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Temporary directory for object files
OBJ_DIR = build
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_LIB) -lreadline

# Only rebuild libft when the library has changed
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

# Rule to compile .c files into .o files inside the temporary directory
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the build directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: $(NAME)

.PHONY: all clean fclean re