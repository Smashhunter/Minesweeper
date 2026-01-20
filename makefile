CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
LIBS = -lncurses

# Sources
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)
TARGET = minesweeper

BUILD ?= debug

all: $(BUILD)

debug: CFLAGS += -g -DDEBUG -O0
debug: LDFLAGS = $(LIBS)
debug: $(TARGET)

release: CFLAGS += -O3 -DNDEBUG
release: LDFLAGS = $(LIBS)
release: $(TARGET)

static: CFLAGS += -O3 -DNDEBUG -static
static: LDFLAGS = -static $(LIBS) -ltinfo
static: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj $(TARGET)

dist: static
	@mkdir -p dist
	tar -czf dist/$(TARGET)-Linux-x64.tar.gz $(TARGET) README.md LICENSE

run: debug
	./$(TARGET)

.PHONY: all debug release static clean dist run
