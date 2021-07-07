NAME		=		philo

FUNCTIONS_DIR	=	../

DIRS			=	./

LIST		= 	log.c						\
                main.c						\
                utils.c						\
               	utils1.c					\
                ft_init_main.c				\
                ft_create_philosopher.c		\
                philo.c						\

SOURCE		=	$(addprefix $(DIRS), $(LIST))

OBJ			=	$(patsubst %.c,%.o,$(SOURCE))
D_FILE		=	$(patsubst %.c,%.d,$(SOURCE))

override D_ALL	?=	$(D_FILE)

override OBJ_ALL	?=	$(OBJ)

INCLUDES  = includes/

FLAGS	=

all: $(NAME)

$(NAME): $(OBJ_ALL)
		gcc $(FLAGS) $(OBJ)  -o $(NAME) -MMD

clean:
		@rm -f $(OBJ) $(D_FILE)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

%.o: %.c
	gcc $(FLAGS) -c -I $(INCLUDES) -c $< -o $@ -MMD

include $(wildcard $(D_ALL))

.PHONY: all clean fclean re
