
CC = wcc386
LINK = wlink

CFLAGS = -bt=os2 -ei -DPLATFORM_SDL=1 -I./local/sdl12/include/

SOURCES = platform_sdl.c test.c

all: clean platform_sdl

clean:
	$(RM) platform_sdl *.exe *.o *.err

platform_sdl: $(SOURCES)
	$(CC) $(CFLAGS) platform_sdl.c
	$(CC) $(CFLAGS) test.c
	$(LINK) SYS os2v2 NAM platform_sdl_os2.exe FIL platform_sdl.o FIL test.o LIBR SDL12.lib
