NAME 		= philo

LIBFT		= lib/libft/
INCLUDES	= includes
SRC_DIR		= src/

SRC			= main.c 

OBJ			= $(SRC:%.c=%.o)

LIB_FLAGS	= -L$(LIBFT) -lft
IFLAG		= -I$(INCLUDES) -I$(LIBFT)
CFLAG		= -Wall -Wextra -Werror
 
CC			= cc
RM			= rm -rf


all:				$(NAME)

.c.o:
					$(CC) -c $(CFLAG) $(IFLAG) -I/usr/include -O3 -c $< -o $(<:.c=.o)

$(NAME):			$(OBJ)
					make -C $(LIBFT)
					$(CC) $(CFLAG) $(OBJ) $(LIB_FLAGS) -o $(NAME)

bonus:				$(BOBJ)
					make -C $(LIBFT)
					$(CC) $(CFLAG) $(BOBJ) $(LIB_FLAGS) -o $(NAME)

clean:				
					make -C $(LIBFT) clean
					$(RM) $(OBJ) $(BOBJ)

fclean: 			clean
					make -C $(LIBFT) fclean
					$(RM) $(NAME)

re:					fclean all

.PHONY: 			all clean fclean re