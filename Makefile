CC = gcc
CFLAGS = -g -Wall
BUILD = build
INC = include

SRC = src
SRCEXT = c
SOURCES = $(shell find $(SRC) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRC)/%,$(BUILD)/%,$(SOURCES:.$(SRCEXT)=.o))

COMMAND = $(CC) $(CFLAGS) -I$(INC)

bin/gSH: $(OBJECTS)
	@echo "Linking Objects ..."
	$(COMMAND) -o bin/gSH $(OBJECTS)
	ctags -R .

$(BUILD)/main.o: $(SRC)/main.c $(INC)/shell.h
	$(COMMAND) -o $(BUILD)/main.o -c $(SRC)/main.c

$(BUILD)/shell.o: $(SRC)/shell.c $(INC)/shell.h $(INC)/globals.h
	$(COMMAND)  -o $(BUILD)/shell.o -c $(SRC)/shell.c
	
$(BUILD)/prompt.o: $(SRC)/prompt.c $(INC)/prompt.h $(INC)/globals.h $(INC)/utils.h $(INC)/errorHandler.h
	$(COMMAND)  -o $(BUILD)/prompt.o -c $(SRC)/prompt.c

$(BUILD)/errorHandler.o: $(SRC)/errorHandler.c $(INC)/errorHandler.h $(INC)/globals.h
	$(COMMAND)  -o $(BUILD)/errorHandler.o -c $(SRC)/errorHandler.c

$(BUILD)/utils.o: $(SRC)/utils.c $(INC)/utils.h $(INC)/globals.h
	$(COMMAND)  -o $(BUILD)/utils.o -c $(SRC)/utils.c

clean: 
	rm $(BUILD)/* bin/gSH
