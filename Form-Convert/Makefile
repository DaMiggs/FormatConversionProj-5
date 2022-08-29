CC = gcc
CFLAGS = -I. -g -w
DEPS = pa5.h
OBJ = PA5Draft.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

PA5X: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
		rm -rf PA5X
		rm -rf *.o

x:
		make
		./PA5X -i csv -o tc9
		