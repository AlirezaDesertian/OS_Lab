CC=gcc
CFLAGS=-Wall -Iinclude
LDFLAGS=-lpthread

TARGET=restaurant
SRC=src/main.c src/banker.c src/chef.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
