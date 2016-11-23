CC=gcc
CFLAGS=-I.
DEPS = parcoursGraphe.h all.h
OBJ = parcoursGraphe.o
GRAPHS = 10K2 kneser72 kneser73 kneser62 kneser83 m47 m95 petersen sierp3
ODIR=obj
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all : $(GRAPHS)

#parcoursGraphe: $(OBJ)
#	gcc -o $@ $^ $(CFLAGS)

10K2 : $(OBJ) 10K2.o
	gcc -o $@ $^ $(CFLAGS)

kneser72 : $(OBJ) kneser72.o
	gcc -o $@ $^ $(CFLAGS)

kneser62 : $(OBJ) kneser62.o
	gcc -o $@ $^ $(CFLAGS)

kneser73 : $(OBJ) kneser73.o
	gcc -o $@ $^ $(CFLAGS)


kneser83 : $(OBJ) kneser83.o
	gcc -o $@ $^ $(CFLAGS)


m47 : $(OBJ) m47.o
	gcc -o $@ $^ $(CFLAGS)


m95 : $(OBJ) m95.o
	gcc -o $@ $^ $(CFLAGS)


petersen : $(OBJ) petersen.o
	gcc -o $@ $^ $(CFLAGS)


sierp3 : $(OBJ) sierp3.o
	gcc -o $@ $^ $(CFLAGS)

.PHONY : clean

clean:
	rm -f *.o $(GRAPHS)
