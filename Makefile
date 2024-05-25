# Compiler
CC=x86_64-w64-mingw32-gcc

# Compiler flags
CFLAGS=-Wall -Wextra -std=c11

# Allegro flags
ALLEGRO_CFLAGS=$(shell pkg-config --cflags allegro-5)
ALLEGRO_LIBS=$(shell pkg-config --libs allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5 allegro_primitives-5 allegro_dialog-5)

# Target
TARGET=game

# Source and object files
SRCDIR=src
SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(ALLEGRO_LIBS)

# Compiling source files
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(ALLEGRO_CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJS)
