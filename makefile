main.o: src/main.c
	gcc -c src/main.c
all: main.o
	gcc main.o
run: all
	./a.out
clean:
	rm *.o a.out
