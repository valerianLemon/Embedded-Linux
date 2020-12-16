CC = gcc

all: www xxxx yyy zzz

www: aa.o bbb.o
	$(CC) -o $@ $^

xxxx: dddd.o
	$(CC) -o $@ $^ -lrt

yyy: eee.o
	$(CC) -o $@ $^ -lpthread

zzz: ff.o
	$(CC) -o $@ $^ -lrt

%.o: %.c
	$(CC) -o $@ -c $^

clean:
	rm *.o www xxxx yyy zzz