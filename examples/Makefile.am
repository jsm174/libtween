noinst_PROGRAMS=hello_world bars

hello_world_SOURCES=hello_world.c
hello_world_CFLAGS=$(SDL_CFLAGS) -I../
hello_world_LDADD=../libtween/libtween.la $(SDL_LIBS)
hello_world_LDFLAGS=-static

bars_SOURCES=bars.c
bars_CFLAGS=$(SDL_CFLAGS) -I../
bars_LDADD=../libtween/libtween.la $(SDL_LIBS)
bars_LDFLAGS=-static
