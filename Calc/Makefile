BIN := calc
SOURCES := main.c
SOURCES2 := calc.c
CC := gcc
.PHONY := clean
$(BIN): $(SOURCES)
		$(CC) $(SOURCES) $(SOURCES2) -o $(BIN) -g

clean:
		rm -rf $(BIN)