
CC = wcc386
LINK = wlink

CFLAGS = -bt=nt -ei -DPLATFORM_SDL=1 -I./local/sdl12/include/

SOURCES = platform_sdl.c test.c

all: clean platform_sdl

clean:
	$(RM) platform_sdl *.exe *.o *.err

platform_sdl: $(SOURCES)
	$(CC) $(CFLAGS) platform_sdl.c
	$(CC) $(CFLAGS) test.c
	$(LINK) SYS nt_win NAM platform_sdl_win32.exe FIL platform_sdl.o FIL test.o LIBF SDLmain.lib LIBR SDL.lib
