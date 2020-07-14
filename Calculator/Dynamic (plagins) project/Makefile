BIN := Calculator
SOURCES := main.c
.PHONY := clean
$(BIN): $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -ldl -g 
		export LD_LIBRARY_PATH=.; ./$(BIN)

clean:
		rm -rf $(BIN)
		