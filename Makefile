# Compiler
C 		= clang
CFLAGS 	= --std=c99
LFLAGS 	= $(SYSTEMC_LIBRARY_DIRS)
LIBS 	= -lm -lcurses

# Folders
DEST_DIR 	= bin
OBJ_DIR 	= build
SRC_DIR 	= src

# File lists
EXECUTABLE 	= $(DEST_DIR)/main
SOURCES 	= $(wildcard $(SRC_DIR)/*.c)
OBJECTS 	= $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Tools
RM 			= rm -rf
MKDIR 		= mkdir -p

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "Linking executable " $(OBJECTS)
	$(MKDIR) $(@D)
	$(C) $(CFLAGS) $(LFLAGS) -o $@ $+ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling " $@
	@mkdir -p $(@D)
	$(C) $(CFLAGS) -c -o $@ $<

clean:
	@echo "Cleaning"
	$(RM) $(OBJ_DIR)
	$(RM) $(DEST_DIR)

%.o: %.c
