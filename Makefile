CC = gcc
CFLAGS = -Wall
BUILD = build
INC = include

SRC = src
SRCEXT = c
SOURCES = $(shell find $(SRC) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRC)/%,$(BUILD)/%,$(SOURCES:.$(SRCEXT)=.o))

COMMAND = $(CC) $(CFLAGS) -I$(INC)


gSH: $(OBJECTS)
	@echo "Linking Objects ..."
	$(COMMAND) -o gSH $(OBJECTS)

debug: CFLAGS += -DDEBUG -g
debug: gSH

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
	
$(BUILD)/ls.o: $(SRC)/ls.c $(INC)/ls.h $(INC)/globals.h $(INC)/errorHandler.h $(INC)/utils.h
	$(COMMAND)  -o $(BUILD)/ls.o -c $(SRC)/ls.c

$(BUILD)/sysCommand.o: $(SRC)/sysCommand.c $(INC)/sysCommand.h $(INC)/globals.h $(INC)/errorHandler.h $(INC)/utils.h $(INC)/processList.h
	$(COMMAND)  -o $(BUILD)/sysCommand.o -c $(SRC)/sysCommand.c

$(BUILD)/pinfo.o: $(SRC)/pinfo.c $(INC)/pinfo.h $(INC)/globals.h
	$(COMMAND)  -o $(BUILD)/pinfo.o -c $(SRC)/pinfo.c

$(BUILD)/signalHandlers.o: $(SRC)/signalHandlers.c $(INC)/signalHandlers.h $(INC)/globals.h $(INC)/prompt.h $(INC)/processList.h
	$(COMMAND)  -o $(BUILD)/signalHandlers.o -c $(SRC)/signalHandlers.c

$(BUILD)/history.o: $(SRC)/history.c $(INC)/history.h $(INC)/globals.h $(INC)/utils.h $(INC)/errorHandler.h
	$(COMMAND)  -o $(BUILD)/history.o -c $(SRC)/history.c

$(BUILD)/processList.o: $(SRC)/processList.c $(INC)/processList.h $(INC)/globals.h
	$(COMMAND)  -o $(BUILD)/processList.o -c $(SRC)/processList.c

$(BUILD)/jobs.o: $(SRC)/jobs.c $(INC)/jobs.h $(INC)/processList.h $(INC)/globals.h
	$(COMMAND)  -o $(BUILD)/jobs.o -c $(SRC)/jobs.c

$(BUILD)/fg.o: $(SRC)/fg.c $(INC)/fg.h $(INC)/processList.h $(INC)/utils.h $(INC)/globals.h
	$(COMMAND)  -o $(BUILD)/fg.o -c $(SRC)/fg.c
	
clean: 
	rm $(BUILD)/* gSH
