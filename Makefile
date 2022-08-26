NAME 		= 	philo

CC			= 	cc

RM 			= 	rm -f

INC			=	-I includes 

CFLAGS		=	-Wall -Wextra -Werror -g

LFLAGS		=	-I./philo -lpthread

FILES		=	philo.c \
				init.c \
				mutex.c \
				threads.c \
				routine.c \
				end_routine.c \
				chopsticks.c \
				print.c \
				sleep.c \
				destroy.c \
				utils.c \

SRCS_PATH	= 	./srcs/

OBJS_PATH	= 	./objs/

OBJS		= 	$(addprefix $(OBJS_PATH), $(FILES:.c=.o))

all:		$(NAME)

$(OBJS_PATH)%.o : 	$(SRCS_PATH)%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< $(OUTPUT_OPTION) $(INC)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LFLAGS) $(OUTPUT_OPTION)

clean:
			$(RM) $(OBJS)
		
fclean:		clean
			$(RM) $(NAME) $(BONUS) $(LIBFT) $(MLX)

re:			fclean all

.PHONY:		all clean fclean re bonus