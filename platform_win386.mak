
CC = wcl386
WBIND = wbind

INCLUDES = -I/usr/local/watcom/h/ -I/usr/local/watcom/h/win/

CFLAGS = -l=win386 -bt=windows -d0 -ox -DPLATFORM_SELF_TEST $(INCLUDES)

SOURCES = platform_win386.c

all: clean platform_win386

clean:
	$(RM) *.o *.err *.rex *.exe

platform_win386: $(SOURCES)
	$(CC) $(CFLAGS) -fe=platform_win386.rex $(SOURCES)
	$(WBIND) platform_win386.exe -n
