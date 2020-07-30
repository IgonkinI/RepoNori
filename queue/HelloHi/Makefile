BIN := SERVER
SOURCES := server.c
BIN1 := CLIENT
SOURCES1 := client.c
CC := gcc
.PHONY := clean
$(BIN): $(SOURCES)
		$(CC) $(SOURCES) -o $(BIN) -lrt -g
		$(CC) $(SOURCES1) -o $(BIN1) -lrt -g

clean:
		rm -rf $(BIN)
		rm -rf $(BIN1)