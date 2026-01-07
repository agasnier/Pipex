NAME = pipex

CC = cc
CFLAGS = -Werror -Wall -Wextra -g

MANDA_DIR = src/mandatory
BONUS_DIR = src/bonus
OBJ_DIR = obj

INC_MANDA = include/mandatory
INC_BONUS = include/bonus

SRCS =	$(MANDA_DIR)/exec.c \
		$(MANDA_DIR)/free.c \
		$(MANDA_DIR)/main.c \
		$(MANDA_DIR)/path.c \
		$(MANDA_DIR)/split.c \
		$(MANDA_DIR)/utils.c \
		$(MANDA_DIR)/utils2.c \

SRCS_BONUS =	$(BONUS_DIR)/exec_bonus.c \
				$(BONUS_DIR)/free_bonus.c \
				$(BONUS_DIR)/get_next_line_bonus.c \
				$(BONUS_DIR)/get_next_line_utils_bonus.c \
				$(BONUS_DIR)/here_doc_bonus.c \
				$(BONUS_DIR)/main_bonus.c \
				$(BONUS_DIR)/path_bonus.c \
				$(BONUS_DIR)/split_bonus.c \
				$(BONUS_DIR)/utils_bonus.c \

HEADER =	

OBJS = $(patsubst $(MANDA_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_BONUS = $(patsubst $(BONUS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_BONUS))

all: $(NAME)

$(NAME): .manda $(OBJS) 
	@echo "Compilation pipex..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation pipex OK."

.manda:
	@if [ -f .bonus ]; then \
		echo "Switch to manda..."; \
		$(MAKE) fclean > /dev/null 2>&1; \
	fi
	@touch .manda

bonus: .bonus $(OBJS_BONUS)
	@echo "Compilation pipex_bonus..."
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)
	@echo "Compilation pipex_bonus OK."

.bonus: 
	@if [ -f .manda ]; then \
		echo "Switch to bonus..."; \
		$(MAKE) fclean > /dev/null 2>&1; \
	fi
	@touch .bonus

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	
%_bonus.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@rm -f .bonus .manda

fclean: clean
	@rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus

