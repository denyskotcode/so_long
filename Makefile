# Compiler and Flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Executable Names
NAME = so_long

# Directories
SRCDIR = src
OBJDIR = obj

LIBFTDIR = libs/libft
FTPRINTF_DIR = libs/libftprintf

# Source Files
SRC = so_long.c

# Object Files
OBJ = $(OBJDIR)/$(SRC:.c=.o)

# Libraries
LIBFT = $(LIBFTDIR)/libft.a
FTPRINTF = $(FTPRINTF_DIR)/libftprintf.a

# Rules for Building
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(FTPRINTF)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -lft -L$(FTPRINTF_DIR) -lftprintf -o $(NAME)

# Rule for Compiling Source Files to Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(LIBFTDIR) -I$(FTPRINTF_DIR) -c $< -o $@

# Ensure Object Directory Exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build Libraries
$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(FTPRINTF):
	$(MAKE) -C $(FTPRINTF_DIR)

# Clean Up
clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(FTPRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(FTPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
