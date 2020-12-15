rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SOURCE      = $(call rwildcard, src/, *.c)
OBJS        = $(SOURCE:%.c=_build/%.o)
HEADER      = $(SOURCE:.c=.h)
OUT         = CText.exe
CC          = gcc
FLAGS       = -O3
DEBUG_FLAGS = -O0

CFLAGS      =  -Wall -Wextra -Werror -rdynamic -std=c99 `pkg-config --cflags gtk+-3.0`
SDL_FLAGS   = `sdl-config --cflags --libs` -lSDL_image `pkg-config --libs gtk+-3.0` `pkg-config gmodule-2.0 --libs`
CPPFLAGS    = `pkg-config --cflags sdl` -MMD `pkg-config --libs gtk+-3.0`


CPPFLAGS= `pkg-config --cflags sdl` -MMD

all: $(OBJS)
	$(CC) $(FLAGS) -g $(OBJS) -o $(OUT) ${SDL_FLAGS} -lm -ldl

debug: $(OBJS)
	$(CC) $(DEBUG_FLAGS) -g $(OBJS) -o $(OUT) ${SDL_FLAGS} -lm -ldl

_build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $(^:_build=)

clean:
	rm -fr $(OBJS) $(OUT) _build/ *.jpg