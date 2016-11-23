CC=gcc
CFLAGS=-I.
DEPS = generateDIMACS.h all.h
OBJ = generateDIMACS.o
GRAPHS = 10K2 kneser72 kneser73 kneser62 kneser83 m47 m95 petersen sierp3 C10 ep chvatal golomb moser hypercube8
ODIR=obj

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

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

C10 : $(OBJ) C10.o
	gcc -o $@ $^ $(CFLAGS)

ep : $(OBJ) ep.o
	gcc -o $@ $^ $(CFLAGS)

chvatal : $(OBJ) chvatal.o
	gcc -o $@ $^ $(CFLAGS)

golomb : $(OBJ) golomb.o
	gcc -o $@ $^ $(CFLAGS)

moser : $(OBJ) moser.o
	gcc -o $@ $^ $(CFLAGS)

hypercube8 : $(OBJ) hypercube8.o
	gcc -o $@ $^ $(CFLAGS)

.PHONY : clean

clean:
	rm -f *.o $(GRAPHS)
