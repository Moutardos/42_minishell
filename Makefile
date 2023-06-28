CC = cc
ODIR = obj
BDIR = bin
SDIR = src
IDIR = include
NAME = $(BDIR)/minishell
LIBFT = $(IDIR)/libft/libft.a
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I$(IDIR)
LFLAGS = -L$(IDIR)/libft -lft -lreadline 
FILES =  exec/exec exec/files_utils \
         minishell/minishell parsing/cmd_utils parsing/parsing_utils1 \
		 parsing/parsing_utils2 parsing/parsing_utils3 parsing/parsing \
		 parsing/parsing_utils4 parsing/parsing_utils5 parsing/parsing_utils6\
		 parsing/parsing_utils7 builtins/echo builtins/pwd builtins/cd\
		 builtins/export builtins/unset builtins/exit parsing/parsing_utils8\
		 handlers/signals exec/redirections
OBJS = $(patsubst %,$(ODIR)/%,$(FILES:=.o))
DEPS = $(patsubst %,$(SDIR)/%,$(FILES:=.d))

all: lib | $(NAME)

lib : $(LIBFT)

$(ODIR):
	mkdir -p $(ODIR)
	mkdir -p $(ODIR)/builtins
	mkdir -p $(ODIR)/handlers
	mkdir -p $(ODIR)/parsing
	mkdir -p $(ODIR)/minishell
	mkdir -p $(ODIR)/exec
	#il faudrait créer un directory pour chaque sous dossier source


$(BDIR):
	mkdir -p $(BDIR)

$(LIBFT):
	$(MAKE) -C $(IDIR)/libft bonus

$(ODIR)/%.o : src/%.c | $(ODIR)
	$(CC) -ggdb3 $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) | $(BDIR)
	$(CC) $(CFLAGS)  -o  $@ $(OBJS) $(LFLAGS)

clean:
	$(RM) -R $(ODIR)
	$(RM) -R .hd
	$(MAKE) -C $(IDIR)/libft $@

fclean: clean
	$(MAKE) -C $(IDIR)/libft $@
	$(RM) -R $(BDIR)

re: fclean all

.PHONY: all clean fclean re