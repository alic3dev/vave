PROJECT_NAME=vave

OUT_DIRECTORY=.
OUT_FILE=$(OUT_DIRECTORY)/$(PROJECT_NAME)

INCLUDE_DIRECTORY=include
OBJECTS_DIRECTORY=objects
SOURCES_DIRECTORY=sources

SOURCE_FILES=$(wildcard $(SOURCES_DIRECTORY)/*.c)
OBJECT_FILES=$(patsubst $(SOURCES_DIRECTORY)/%.c, $(OBJECTS_DIRECTORY)/%.o, $(SOURCE_FILES))

CEXIL_INCLUDE_DIRECTORY=../cexil/include
CEXIL_OBJECT_FILE=../cexil/objects/cexil.o

CC=gcc
C_FLAGS=-O3 -I$(INCLUDE_DIRECTORY) -I$(CEXIL_INCLUDE_DIRECTORY)

$(OUT_FILE): $(OBJECT_FILES)
	$(CC) $(C_FLAGS) $^ $(CEXIL_OBJECT_FILE) -o $@

$(OBJECTS_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.c
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	-rm $(OUT_FILE) $(OBJECTS_DIRECTORY)/*.o 2> /dev/null

