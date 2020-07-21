BIN := SHOP
SOURCES := main.c
CC := gcc
.PHONY := clean
$(BIN): $(SOURCES)
		$(CC) $(SOURCES) -o $(BIN) -pthread -g

clean:
		rm -rf $(BIN)