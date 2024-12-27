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
MLXDIR = libs/minilibx-linux

# Source Files
SRC = so_long.c

# Object Files
OBJ = $(OBJDIR)/$(SRC:.c=.o)

# Libraries
LIBFT = $(LIBFTDIR)/libft.a
FTPRINTF = $(FTPRINTF_DIR)/libftprintf.a
MLX = $(MLXDIR)/libmlx.a

# Rules for Building
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(FTPRINTF) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -lft \
		-L$(FTPRINTF_DIR) -lftprintf \
		-L$(MLXDIR) -lmlx -lXext -lX11 \
		-o $(NAME)

# Rule for Compiling Source Files to Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(LIBFTDIR) -I$(FTPRINTF_DIR) -I$(MLXDIR) -c $< -o $@

# Ensure Object Directory Exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build Libraries
$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(FTPRINTF):
	$(MAKE) -C $(FTPRINTF_DIR)

$(MLX):
	$(MAKE) -C $(MLXDIR)

# Clean Up
clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(FTPRINTF_DIR) clean
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(FTPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

