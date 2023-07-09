
CC ?= gcc

CFLAGS += -std=c99 -pedantic -Wall -Wextra

SOURCES = unpak.c

EXEC ?= unpak

all: clean $(EXEC)

clean:
	$(RM) $(EXEC)

$(EXEC): $(SOURCES)
	$(CC) -o $(EXEC) $(SOURCES) $(CFLAGS)
