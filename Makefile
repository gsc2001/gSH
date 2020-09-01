CC = gcc
CFLAGS = -Wall
BUILD = build
INC = include

SRC = src
SRCEXT = c
SOURCES = $(shell find $(SRC) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRC)/%,$(BUILD)/%,$(SOURCES:.$(SRCEXT)=.o))

COMMAND = $(CC) $(CFLAGS) -I$(INC)

debug: CFLAGS += -DDEBUG -g
debug: bin/gSH

bin/gSH: $(OBJECTS)
	@echo "Linking Objects ..."
	$(COMMAND) -o bin/gSH $(OBJECTS)

$(BUILD)/main.o: $(SRC)/main.c $(INC)/shell.h
	$(COMMAND) -o $(BUILD)/main.o -c $(SRC)/main.c

$(BUILD)/shell.o: $(SRC)/shell.c $(wildcard $(INC)/*.h)
	$(COMMAND)  -o $(BUILD)/shell.o -c $(SRC)/shell.c
	
$(BUILD)/prompt.o: $(SRC)/prompt.c $(INC)/prompt.h $(INC)/globals.h $(INC)/utils.h $(INC)/errorHandler.h
	$(COMMAND)  -o $(BUILD)/prompt.o -c $(SRC)/prompt.c

$(BUILD)/errorHandler.o: $(SRC)/errorHandler.c $(INC)/errorHandler.h $(INC)/globals.h
	$(COMMAND)  -o $(BUILD)/errorHandler.o -c $(SRC)/errorHandler.c

$(BUILD)/utils.o: $(SRC)/utils.c $(INC)/utils.h $(INC)/globals.h
	$(COMMAND)  -o $(BUILD)/utils.o -c $(SRC)/utils.c

$(BUILD)/parse.o: $(SRC)/parse.c $(INC)/parse.h $(INC)/globals.h $(INC)/utils.h
	$(COMMAND)  -o $(BUILD)/parse.o -c $(SRC)/parse.c

$(BUILD)/mpwd.o: $(SRC)/mpwd.c $(INC)/mpwd.h $(INC)/globals.h $(INC)/errorHandler.h
	$(COMMAND)  -o $(BUILD)/mpwd.o -c $(SRC)/mpwd.c

$(BUILD)/cd.o: $(SRC)/cd.c $(INC)/cd.h $(INC)/globals.h $(INC)/errorHandler.h
	$(COMMAND)  -o $(BUILD)/cd.o -c $(SRC)/cd.c

$(BUILD)/echo.o: $(SRC)/echo.c $(INC)/echo.h $(INC)/globals.h $(INC)/utils.h
	$(COMMAND)  -o $(BUILD)/echo.o -c $(SRC)/echo.c
	
clean: 
	rm $(BUILD)/* bin/gSH
