BIN := redactor
SOURCES := main.c
CC := gcc
.PHONY := clean
$(BIN): $(SOURCES)
		$(CC) $(SOURCES) -o $(BIN) -lncurses -lpanel -lmenu -g 

clean:
		rm -rf $(BIN)