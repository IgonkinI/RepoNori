BIN := FileManager
SOURCES := main.c
CC := gcc
.PHONY := clean
$(BIN): $(SOURCES)
		$(CC) $(SOURCES) -o $(BIN) -lncurses -lpanel -g 

clean:
		rm -rf $(BIN)