
CFLAGS = -pedantic -Wall -DPLATFORM_SELF_TEST `sdl-config --libs --cflags`

SOURCES = platform_sdl.c

all: clean platform_sdl

clean:
	$(RM) platform_sdl *.exe

platform_sdl: $(SOURCES)
	$(CC) -o platform_sdl $(SOURCES) $(CFLAGS) 
