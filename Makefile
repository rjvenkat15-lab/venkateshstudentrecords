CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Iinclude
TARGET = student_record_management_percentage.exe
SOURCES = src/main.c src/insert.c src/display.c src/search.c src/update.c src/delete.c src/sort.c src/file.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) include/student.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	$(RM) $(TARGET)
