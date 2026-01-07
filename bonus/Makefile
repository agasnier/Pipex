NAME = pipex

CC = cc
CFLAGS = -Werror -Wall -Wextra -g

SRCS =	exec.c \
		free.c \
		main.c \
		path.c \
		split.c \
		utils.c \

SRCS_BONUS =	get_next_line_utils.c \
				get_next_line.c \
				here_doc.c \

HEADER =	

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS:.c=_bonus.o) $(SRCS_BONUS:.c=_bonus.o)

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
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@rm -f .bonus .manda

fclean: clean
	@rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re bonus

