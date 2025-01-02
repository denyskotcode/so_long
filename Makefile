# Compiler and Flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

# Executable Name
NAME = so_long

# Directories
SRCDIR = src
OBJDIR = obj

LIBFTDIR = libs/libft
FTPRINTF_DIR = libs/libftprintf
MLXDIR = libs/minilibx-linux
GNL_DIR = libs/get_next_line

# Source Files
SRC = so_long.c check_lines.c check_map_file.c declaration_structures.c allocate_map.c render_map.c process_functions.c textures.c $(GNL_DIR)/get_next_line.c

# Object Files
OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

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
	$(CC) $(CFLAGS) -I$(LIBFTDIR) -I$(FTPRINTF_DIR) -I$(MLXDIR) -I$(GNL_DIR) -c $< -o $@

$(OBJDIR)/%.o: $(GNL_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(LIBFTDIR) -I$(FTPRINTF_DIR) -I$(MLXDIR) -I$(GNL_DIR) -c $< -o $@

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
