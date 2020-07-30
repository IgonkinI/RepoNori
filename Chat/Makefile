BIN := SERVER
SOURCES := server.c
BIN1 := CLIENT
SOURCES1 := client.c
CC := gcc
.PHONY := clean
$(BIN): $(SOURCES)
		$(CC) $(SOURCES) -o $(BIN) -lrt -g -Wall
		$(CC) $(SOURCES1) -o $(BIN1) -lrt -pthread -lncurses -g -Wall
clean:
		rm -rf $(BIN)
		rm -rf $(BIN1)