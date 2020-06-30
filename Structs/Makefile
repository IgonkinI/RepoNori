BIN := pointerStruct
SOURCES := pointerStruct.c
BIN2 := Phone_Book
SOURCES2 := Phone_Book.c
SOURCES3 := struct.c
CC := gcc
.PHONY := clean

all: $(BIN) $(BIN2)

$(BIN): $(SOURCES)
		$(CC) $(SOURCES) -o $(BIN) -g
$(BIN2): $(SOURCES2)
		$(CC) $(SOURCES2) $(SOURCES3) -o $(BIN2) -g

clean:
		rm -rf $(BIN)
		rm -rf $(BIN2)