# Makefile pour "Projet Mise a niveau"
#
# 25/10/2015 - contact@mickael-bernardini.fr

#SHELL  = /bin/zsh
CC     = gcc
CFLAGS = -Wall -W -std=c89 -pedantic -Iinclude

# fichier a compiler
EXECS = main

.c.o :
	$(CC) -c $(CFLAGS) $*.c

all :: $(EXECS) 

$(EXECS) : %: %.o
	$(CC) -o $@ $@.o

clean ::
	\rm -f *.o core
