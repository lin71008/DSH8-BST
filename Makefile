CC := gcc
CFLAGS := -std=gnu99 -O0 -g -Wall -Werror
OBJECT := $(patsubst %.c,%.o,$(wildcard *.c))

all: $(OBJECT)
	$(CC) $(OBJECT) $(CFLAGS) -o main.exe

$(OBJECT): %o:%c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJECT)
	rm *.exe
