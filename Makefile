CC=gcc
CFLAGS=-I -Wall -Werror -Wextra -O -std=gnu11 -l ws2_32
DEPS = server.h
OBJ = server.o client.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: $(OBJ)
	$(CC) -o server.exe server.c $(CFLAGS) 
	$(CC) -o client.exe client.c $(CFLAGS)

.PHONY: clean

clean:
	del $(ODIR)/*.o *~ core $(INCDIR)/*~ 