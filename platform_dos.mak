
CC = i586-pc-msdosdjgpp-gcc

CFLAGS = -pedantic -Wall -DPLATFORM_SELF_TEST

SOURCES = platform_dos.c test.c

all: clean platform_dos

clean:
	$(RM) *.exe

platform_dos: $(SOURCES)
	$(CC) -o platform_dos.exe $(SOURCES) $(CFLAGS) 
