NAME=	templatedList

SRC=	ListAPI/ListAPI.c \
	Examples/main.c
OBJ=	$(SRC:.c=.o)

INC= -IListAPI -IExamples

CFLAGS=	-W -Wall

$(NAME):$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.c.o:
	$(CC) -c $< -o $@ $(INC)