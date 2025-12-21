main.o: src/main.c
	gcc -c src/main.c
cli.o: src/cli/cli.c
	gcc -c src/cli/cli.c
scramble.o: src/scramble/scramble.c
	gcc -c src/scramble/scramble.c
timer.o: src/timer/timer.c
	gcc -c src/timer/timer.c
term.o: src/term/term.c
	gcc -c src/term/term.c
db.o: src/db/db.c
	gcc -c src/db/db.c
all: main.o cli.o scramble.o timer.o term.o db.o
	gcc -O3 -lsqlite3 main.o cli.o scramble.o timer.o term.o db.o -o cubing_timer
clean:
	rm *.o cubing_timer
