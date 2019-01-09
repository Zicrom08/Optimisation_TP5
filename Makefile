CC = gcc
CFLAGS = -pipe -march=native -std=c99 -Wall -Wextra -O3
LDLIBS =
LDFLAGS = -pipe

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

EXE = prog

.PHONY:	clean mrproper

all:	depend $(EXE)

$(EXE): depend $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# makedepend: le package xutils-dev doit être installé
#EDIT personnel : (sous Ubuntu/Debian c'est valide)
depend:
	@makedepend -- $(CFLAGS) -- -Y $(SRCS) 2> /dev/null

clean:
	rm -f *.o

mrproper:	clean
	rm -f $(EXE)

# DO NOT DELETE THIS LINE

ensemble.o: ensemble.h
file.o: file.h
liste.o: liste.h
kruskal.o: kruskal.h graphe.h ListeAdj.h liste.h file.h ensemble.h
filePrioritesMin.o: filePrioritesMin.h graphe.h ListeAdj.h liste.h file.h
graphe.o: graphe.h ListeAdj.h liste.h file.h
main.o: graphe.h ListeAdj.h liste.h file.h kruskal.h ensemble.h prim.h
main.o: filePrioritesMin.h cycle.h
ListeAdj.o: ListeAdj.h liste.h
cycle.o: cycle.h graphe.h ListeAdj.h liste.h file.h
prim.o: prim.h graphe.h ListeAdj.h liste.h file.h filePrioritesMin.h
