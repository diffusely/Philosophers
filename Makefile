NAME 		= philo

INCLUDES	= includes
SRC_DIR		= src/

SRC			= main.c \
			  $(SRC_DIR)utils.c \
			  $(SRC_DIR)valid.c \
			  $(SRC_DIR)free.c \
			  $(SRC_DIR)init.c \
			  $(SRC_DIR)philo.c 

OBJ			= $(SRC:%.c=%.o)

IFLAG		= -I$(INCLUDES)
CFLAG		= #-Wall -Wextra -Werror
 
CC			= cc
RM			= rm -rf


all:				$(NAME)

.c.o:
					$(CC) -c $(CFLAG) $(IFLAG) -I/usr/include -O3 -c $< -o $(<:.c=.o)

$(NAME):			$(OBJ)
					$(CC) $(CFLAG) $(OBJ) -o $(NAME)

bonus:				$(BOBJ)
					$(CC) $(CFLAG) $(BOBJ) -o $(NAME)

clean:				
					$(RM) $(OBJ)

fclean: 			clean
					$(RM) $(NAME)

re:					fclean all

.PHONY: 			all clean fclean re