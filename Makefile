########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ggdb
IFLAGS=-I./
LDFLAGS=-L./
#LDLIBS=-lstack
LDLIBS=-lstack_fp
### -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EJS = p3_e1
########################################################
OBJECTSP1E1 = p1_e1.o vertex.o
OBJECTSP1E2 = p1_e2.o graph.o vertex.o
OBJECTSP1E3 = p1_e3.o graph.o vertex.o
#OBJECTSP2E1A = p2_e1a.o libstack.a
#OBJECTSP2E1B = p2_e1b.o vertex.o libstack.a
#OBJECTSP2E2	 = p2_e2.o vertex.o graph.o algorithms.o libstack.a
OBJECTSP2E1A = p2_e1a.o libstack_fp.a
OBJECTSP2E1B = p2_e1b.o vertex.o libstack_fp.a
OBJECTSP2E2	 = p2_e2.o vertex.o graph.o algorithms.o libstack_fp.a
OBJECTSP3E1 = p3_e1.o vertex.o delivery.o libqueue.a
########################################################

all: $(EJS) libstack_fp.a

algorithms.o: algorithms.c algorithms.h vertex.h graph.h libstack_fp.a
	$(CC) $(CFLAGS) $(IFLAGS) -c algorithms.c

p1_e1: $(OBJECTSP1E1)
	$(CC) $(CFLAGS) -o p1_e1 $(OBJECTSP1E1)

p1_e2: $(OBJECTSP1E2)
	$(CC) $(CFLAGS) -o p1_e2 $(OBJECTSP1E2)

p1_e3: $(OBJECTSP1E3)
	$(CC) $(CFLAGS) -o p1_e3 $(OBJECTSP1E3)

p2_e1a: $(OBJECTSP2E1A)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e1b: $(OBJECTSP2E1B)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e2: $(OBJECTSP2E2)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p3_e1: $(OBJECTSP3E1)
	$(CC) -o $@ $^ $(LDFLAGS) -lqueue $(LIBS)

p3_e1.o: p3_e1.c vertex.h delivery.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e2.o: p2_e2.c vertex.h graph.h algorithms.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e1b.o: p2_e1b.c vertex.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p2_e1a.o: p2_e1a.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p1_e3.o: p1_e3.c vertex.h graph.h
	$(CC) $(CFLAGS) -c p1_e3.c

p1_e2.o: p1_e2.c vertex.h graph.h
	$(CC) $(CFLAGS) -c p1_e2.c

p1_e1.o: p1_e1.c vertex.h
	$(CC) $(CFLAGS) -c p1_e1.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c graph.h vertex.h
	$(CC) $(CFLAGS) -c graph.c

delivery.o: delivery.c delivery.h vertex.h
	$(CC) $(CFLAGS) -c delivery.c

###########################################################################################################################################
######	CREA LA BIBLIOTECA CON LAS FUENTES: stack.c file_utils.c
###########################################################################################################################################

stack.o: stack.c stack.h file_utils.h
	$(CC) -c -o $@ $< $(CFLAGS)

file_utils.o: file_utils.c file_utils.h
	$(CC) -c -o $@ $< $(CFLAGS)

libstack_fp.a: file_utils.o stack.o
	$(AR) rcs $@ $^

libs: libstack_fp.a

clear:
	rm -rf *.o libstack_fp.a

clean:
	rm -rf *.o libstack_fp.a $(EJS)

run:
	@echo ">>>>>>Running p1_e1"
	./p1_e1
	@echo ">>>>>>Running p1_e2"
	./p1_e2 
	@echo ">>>>>>Running p1_e3"
	./p1_e3 g1.txt
	@echo ">>>>>>Running p2_e1a"
	./p2_e1a grades1.txt grades2.txt
	@echo ">>>>>>Running p2_e1b"
	./p2_e1b cities1.txt cities2.txt
	@echo ">>>>>>Running p2_e2"
	./p2_e2 g2.txt 100 700

runv:
	@echo ">>>>>>Running p1_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p1_e1
	@echo ">>>>>>Running p1_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p1_e2 
	@echo ">>>>>>Running p1_e3 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p1_e3 g1.txt
	@echo ">>>>>>Running p2_e1a with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e1a grades1.txt grades2.txt
	@echo ">>>>>>Running p2_e1b with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e1b cities1.txt cities2.txt
	@echo ">>>>>>Running p2_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e2 g2.txt 100 700
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e1 requests.txt
