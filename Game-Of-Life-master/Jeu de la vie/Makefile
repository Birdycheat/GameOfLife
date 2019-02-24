main.exe : main.o
	gcc -o main.exe main.o -Werror -lSDL2 -lm
main.o : main.c
	gcc -o main.o -c main.c -Werror -lSDL2 -lm
clean:
	rm -rf *.o
mrproper: clean
	rm -rf main.exe
