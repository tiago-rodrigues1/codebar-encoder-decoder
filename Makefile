FLAGS= -g -std=c99 -Wall -Wextra -Werror -pedantic

all: encoder
encoder: codebar.o pbm.o
	gcc encoder.c codebar.o pbm.o -o encoder $(FLAGS)
pbm.o: src/pbm.c
	gcc src/pbm.c -c $(FLAGS)
codebar.o: src/codebar.c
	gcc src/codebar.c -c $(FLAGS)
clean:
	rm -rf *.o