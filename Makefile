CC = gcc
CFLAGS = -I src/include
LDFLAGS = -L src/lib -lmingw32 -lSDL3
TARGET = main.exe
SRC = *.c

all:
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)
