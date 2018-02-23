
.PHONY: clean

# Les règles de compilation peuvent utiliser les variables suivantes
# Consultez la documentation de make pour en savoir plus (et en
# trouver d’autres)
#
# $@  Le nom de la cible
# $<  Le nom de la première dépendance
# $^  La liste des dépendances

CC      = gcc

CFLAGS  = -Wall -Wextra -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g


exec : course multif

observe: observe.o
		$(CC) $(LDFLAGS) -g -Wimplicit -o $@ $^
multif: multif.o
	$(CC) $(LDFLAGS) -g -Wimplicit -o $@ $^
course: course.o
	$(CC) $(LDFLAGS) -g -Wimplicit -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -g -Wimplicit -c $<

test:
	./test.sh
clean:
	rm *.o
