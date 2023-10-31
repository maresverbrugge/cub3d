# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mverbrug <mverbrug@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/22 09:54:35 by mverbrug      #+#    #+#                  #
#    Updated: 2023/09/19 14:33:30 by mverbrug      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#========================================#
#========== STANDARD VARIABLES ==========#
#========================================#

OBJ_DIR		:=	obj
SRC_DIR		:=	src
INC_DIR		:=	includes

#========================================#
#============= COMPILATION ==============#
#========================================#

RM				=	rm -f
CC				:=	gcc
C_FLAGS			?=	-Wall -Werror -Wextra

ifdef DEBUG
	C_FLAGS		+=	-g
endif

ifdef FSAN
	C_FLAGS		+=	-g -fsanitize=address
endif

COMPILE		:=	$(CC) $(C_FLAGS)

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME				:=	cub3D

LIBFT 				:=	libft/libft.a

MLX					:=	MLX42/build/libmlx42.a

MLX_MACOS_FLAGS		=	-I include -lglfw3 -framework Cocoa \
						-framework OpenGL -framework IOKit

MLX_LINUX_FLAGS		=	-ldl -lglfw -pthread -lm

UNAME				:=	$(shell uname -s)

SRC					:=	\
						colour.c				\
						draw_vertical.c			\
						error_handle.c			\
						free.c					\
						get_start_position.c	\
						hookers.c				\
						init.c					\
						main.c					\
						map.c					\
						mini_map_colours.c		\
						mini_map.c				\
						mlx.c					\
						move.c					\
						parser_checks.c			\
						parser.c				\
						player_view.c			\
						raycasting.c			\
						read_sdf.c				\
						rotate.c				\
						tests.c					\
						utils.c

SRC					:=	$(SRC:%=$(SRC_DIR)/%)
OBJ					:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP					:=	$(OBJ:%.o=%.d)

ifeq ($(UNAME), Linux)
    MLX_FLAGS 		:= -D $(MLX_LINUX_FLAGS)
else
    MLX_FLAGS 		:= -D $(MLX_MACOS_FLAGS)
endif

#=============== INCLUDES ===============#

INCLUDE				:=	-I $(INC_DIR) \
						-I ./MLX42/include \
						-I ./libft

#========================================#
#============== RECIPIES  ===============#
#========================================#

all: $(NAME)

$(NAME):	$(OBJ) $(LIBFT) $(MLX)
			@$(COMPILE) $(INCLUDE) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
			@echo "$(P)$(BOLD)================ DONE COMPILING ================$(RESET)"
			@echo "\n$(W)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$(RESET)\n"
			@echo "          $(BOLD) $(Y)$@ $(G)$@ $(B)$@ $(P)$@ $(R)$@!$(RESET)"
			@echo "\n$(W)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$(RESET)\n"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c | $(OBJ_DIR)
			@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $<
			@echo "$(B)$(BOLD)COMPILING: $(RESET)$(B)$(if $(findstring -g,$(C_FLAGS)), debug (-g)) $(notdir $<)\
			$(RESET)"

$(OBJ_DIR):
			@mkdir $(OBJ_DIR)

clean:
			@rm -rf $(OBJ_DIR)
			@$(MAKE) clean -C libft
			@rm -rf ./MLX42/build
			@echo "$(C)$(BOLD)CLEANING:   $(RESET)$(C)$(NAME)$(RESET)"

fclean:
			@rm -f $(NAME)
			@rm -rf $(OBJ_DIR)
			@$(MAKE) clean -C libft
			@$(MAKE) fclean -C libft
			@echo "$(C)$(BOLD)FCLEANING:  $(RESET)$(C)$(NAME)$(RESET)"

re: 		fclean
			@$(MAKE)

debug:		fclean
			@$(MAKE) DEBUG=1
			@echo "$(P)$(BOLD)================== DEBUG MODE ==================$(RESET)"

fsan:		fclean
			@$(MAKE) FSAN=1
			@echo "$(P)$(BOLD)================ FSAN ADDRESS ==================$(RESET)"

gclean:		fclean
			@$(RM) *.DS_Store ./.DS_Store *.out
			@$(RM) ./libft/.DS_Store ./libft/libft_src/.DS_Store
			@$(RM) *.out ./libft/libft.a.5OzDFi
			@rm -rf *.dSYM
			@echo "$(C)$(BOLD)DELETED:    $(RESET)$(C)*._DS_Store and *.dSYM files"
			@echo "$(G)$(BOLD)=============== READY TO COMMIT ===============$(RESET)"

norm: 		fclean
			@echo "$(Y)$(BOLD)NORMINETTE: $(RESET)$(Y)$(NAME)$(RESET)$(G)"
			@norminette libft src includes/cub3d.h

.PHONY:		all clean fclean re debug fsan gclean norm

#========================================#
#============== LIBRARIES ===============#
#========================================#

$(LIBFT): 
			@$(MAKE) -C libft
			@echo "$(G)$(BOLD)CREATED:   $(RESET)$(G) libft.a $(RESET)"

$(MLX):
			@cmake ./MLX42 -B ./MLX42/build && $(MAKE) -C ./MLX42/build -j4
			@echo "$(G)$(BOLD)CREATED:   $(RESET)$(G) libmlx42.a $(RESET)"


#========================================#
#=============== COLOURS ================#
#========================================#

BOLD      := \033[1m
RESET     := \033[0m
C         := \033[36m
P         := \033[35m
B         := \033[34m
Y         := \033[33m
G         := \033[32m
R         := \033[31m
W         := \033[0m
