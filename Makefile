CC=gcc
CFLAGS=-I -Wall -Werror -Wextra -O -std=gnu11
DEPS = server.h
OBJ = server.o client.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: $(OBJ)
	$(CC) -o server.exe server.c $(CFLAGS) -lws2_32
	$(CC) -o client.exe client.c $(CFLAGS) -lws2_32

.PHONY: clean

clean:
	del $(ODIR)/*.o *~ core $(INCDIR)/*~ 