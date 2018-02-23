CC      = gcc

CFLAGS  = -Wall -Wextra -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

LDFLAGS = -g

tout: args do_without_makeargv do

# Pour construire le programme binaire « args », il est nécessaire de
# faire l’édition des liens de tous les .o qui contiennent son code
# « args » dépend donc de « args.o » mais aussi de « makeargv.o »
args: makeargv.o args.o
do_without_makeargv: do_without_makeargv.o
do : do.o
# Règles implicites pour la compilation et l’édition de liens
%.o: %.c
	${CC} ${CFLAGS} -c $<

%: %.o
	${CC} ${LDFLAGS} -o $@ $^

%: %.c

test:
	./test.sh
# Règles de nettoyage
clean:
	rm -f core *.o

realclean: clean
	rm -f args

.PHONY: tout clean realclean
