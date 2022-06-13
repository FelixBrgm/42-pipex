CFLAGS := -Wall -Werror -Wextra
AR := ar rcs

CFILES :=  children.c input.c where.c here_doc.c utils.c
CFILES := $(addprefix src/, $(CFILES))
OFILES := $(CFILES:.c=.o)

NAME = pipex

LIBS = libs

all: $(NAME)

$(NAME): $(OFILES) src/pipex.o
	make -C $(LIBS)
	gcc $(CFLAGS) src/pipex.c $(OFILES) -o  $(NAME) -L $(LIBS) -l s

bonus: $(OFILES) src/pipex_bonus.o
	make -C $(LIBS)
	gcc $(CFLAGS) src/pipex_bonus.c $(OFILES) -o  $(NAME) ./libs/libs.a

clean: 
	make clean -C $(LIBS)
	rm -f $(OFILES)
	rm -f src/pipex.o
	rm -f src/pipex_bonus.o

fclean: clean
	make fclean -C $(LIBS)
	rm -f $(NAME)


re: fclean all

