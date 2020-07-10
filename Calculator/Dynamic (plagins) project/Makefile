BIN := Calculator
SOURCES := main.c
.PHONY := clean
DIR := plagins
LIB := libcalc.so
$(BIN): $(SOURCES)
		gcc -fPIC -c $(DIR)/*.c
		gcc -shared *.o -o $(LIB)
		rm -rf *.o
		gcc $(SOURCES) -o $(BIN) -ldl -g 
		export LD_LIBRARY_PATH=.; ./$(BIN)

clean:
		rm -rf $(BIN)
		rm -rf $(LIB)