CFLAGS := -Wall -Werror -Wextra
AR := ar rcs

CFILES :=  pipex.c children.c
CFILES := $(addprefix src/, $(CFILES))
OFILES := $(CFILES:.c=.o)

NAME = pipex

LIBS = libs

all: $(NAME)

$(NAME): $(OFILES)
	make -C $(LIBS)
	gcc $(CFLAGS) $(OFILES) -o $(NAME) -L $(LIBS) -l s

clean: 
	make clean -C $(LIBS)
	rm -f $(OFILES)


fclean: clean
	make fclean -C $(LIBS)
	rm -f $(NAME)


re: fclean all

.SILENT: