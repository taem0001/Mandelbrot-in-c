all:
	gcc *.c -I src/include -L src/lib -lmingw32 -lSDL3 -fopenmp -o main.exe
