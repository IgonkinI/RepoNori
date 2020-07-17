BIN := redactor
SOURCES := main.c
CC := gcc
.PHONY := clean
$(BIN): $(SOURCES)
		$(CC) $(SOURCES) -o $(BIN) -lncurses -g 

clean:
		rm -rf $(BIN)