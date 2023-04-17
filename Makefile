########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LSLIBS=-lstack_fp
LQLIBS=-lqueue_fp
LLLIBS=-llist_fp
### -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EJS = p3_e1 p3_e2 p3_e3
########################################################
OBJECTSP3E1 = p3_e1.o vertex.o delivery.o libqueue_fp.a
OBJECTSP3E2 = p3_e2.o graph.o vertex.o delivery.o algorithms.o libstack_fp.a libqueue_fp.a
OBJECTSP3E3 = p3_e3.o liblist_fp.a
########################################################

all: $(EJS) libs libq

algorithms.o: algorithms.c algorithms.h vertex.h graph.h stack.h
	$(CC) $(CFLAGS) $(IFLAGS) -c algorithms.c

p3_e1: $(OBJECTSP3E1)
	$(CC) -o $@ $^ $(LDFLAGS) $(LQLIBS) $(LIBS)

p3_e2: $(OBJECTSP3E2)
	$(CC) -o $@ $^ $(LDFLAGS) $(LQLIBS) $(LSLIBS) $(LIBS)

p3_e3: $(OBJECTSP3E3)
	$(CC) -o $@ $^ $(LDFLAGS) $(LLLIBS) $(LIBS)

p3_e3.o: p3_e3.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p3_e2.o: p3_e2.c graph.h vertex.h delivery.h algorithms.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p3_e1.o: p3_e1.c vertex.h delivery.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c graph.h vertex.h
	$(CC) $(CFLAGS) -c graph.c

delivery.o: delivery.c delivery.h vertex.h
	$(CC) $(CFLAGS) -c delivery.c

###########################################################################################################################################
######	CREA LAS BIBLIOTECAS CON LAS FUENTES: file_utils.c, stack.c, queue.c, list.c		######
###########################################################################################################################################

stack.o: stack.c stack.h file_utils.h
	$(CC) -c -o $@ $< $(CFLAGS)

file_utils.o: file_utils.c file_utils.h
	$(CC) -c -o $@ $< $(CFLAGS)

libstack_fp.a: file_utils.o stack.o
	$(AR) rcs $@ $^

libs: libstack_fp.a

queue.o: queue.c queue.h
	$(CC) -c -o $@ $< $(CFLAGS)

libqueue_fp.a: file_utils.o queue.o
	$(AR) rcs $@ $^

libq: libqueue_fp.a

list.o: list.c list.h file_utils.h
	$(CC) -c -o $@ $< $(CFLAGS)

liblist_fp.a: file_utils.o list.o
	$(AR) rcs $@ $^

libl: liblist_fp.a

###########################################################################################################################################

clear:
	rm -rf *.o libstack_fp.a libqueue_fp.a liblist_fp.a

clean:
	rm -rf *.o *.gch libstack_fp.a libqueue_fp.a liblist_fp.a $(EJS)

run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 requests.txt
	@echo ">>>>>>Running p3_e2"
	./p3_e2 city_graph.txt 100 700
	@echo ">>>>>>Running p3_e2"
	./p3_e2 city_graph.txt 100 400
	@echo ">>>>>>Running p3_e3"
	./p3_e3 grades.txt 1
	@echo ">>>>>>Running p3_e3"
	./p3_e3 grades.txt -1

runv:
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e1 requests.txt
	@echo ">>>>>>Running p3_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e2 city_graph.txt 100 700
	@echo ">>>>>>Running p3_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e2 city_graph.txt 100 400
	@echo ">>>>>>Running p3_e3 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e3 grades.txt 1
	@echo ">>>>>>Running p3_e3 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e3 grades.txt -1
