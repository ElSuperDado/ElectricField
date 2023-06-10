CC = -gcc
CFLAGS = -g -Wall -Wextra -pedantic #-Werror
LINKS = -lm
SANITIZERS  = -fsanitize=address -fsanitize=leak
SDL = -lSDL2

TARGET = ef_sim
ROOT = .
SRC_FOLDER = ./src
LIBS_FOLDER = ./libs

SOURCES_SRC = $(wildcard $(SRC_FOLDER)/*.c)
SOURCES_LIBS = $(wildcard $(LIBS_FOLDER)/*.c)
SOURCES_MAIN = $(wildcard $(ROOT)/*.c)

OBJECTS_EF = $(SOURCES_SRC:.c=.o)
OBJECTS_LIBS = $(SOURCES_LIBS:.c=.o)
OBJECTS_MAIN = $(SOURCES_MAIN:.c=.o)

$(TARGET) : $(OBJECTS_MAIN) $(OBJECTS_EF) $(OBJECTS_LIBS) $(SDL)
	$(CC) $(CFLAGS) $(SANITIZERS) -o $@ $^ $(LINKS)

.PHONY: clean rebuild exe

clean:
	rm -f *.o $(TARGET) $(OBJECTS_MAIN) $(OBJECTS_EF) $(OBJECTS_LIBS)

rebuild:
	clean $(TARGET)

exe:
	./$(TARGET)
