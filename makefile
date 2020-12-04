CC=gcc
CFLAGS=-g
DEPS = Vista.h Motor.h
OBJ = Netflix.o Vista.o Motor.o

Netflix: $(OBJ)
	$(CC) $(CFLAGS) -o Netflix $(OBJ)

Netflix.o: Netflix.c $(DEPS)
	$(CC) $(CFLAGS) -c Netflix.c

Vista.o: Vista.c
	$(CC) $(CFLAGS) -c Vista.c

Motor.o: Motor.c
	$(CC) $(CFLAGS) -c Motor.c

clean:
	rm *.o
