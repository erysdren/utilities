
CC = wcl386

CFLAGS = -l=os2v2 -bt=os2 -ei -DPLATFORM_SELF_TEST -I./local/sdl12/include/

SOURCES = platform_sdl.c SDL12.lib

all: clean platform_sdl

clean:
	$(RM) platform_sdl *.exe *.o *.err

platform_sdl: $(SOURCES)
	$(CC) $(CFLAGS)  -Fo=platform_sdl $(SOURCES) 
