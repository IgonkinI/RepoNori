BIN := Calculator
SOURCES := main.c
.PHONY := clean

$(BIN): $(SOURCES)
		gcc -fPIC -c library/*.c
		gcc -shared -o libcalc.so *.o
		gcc -c $(SOURCES)
		gcc main.o -L. -lcalc -o $(BIN)
		rm -rf *.o
		export LD_LIBRARY_PATH=.; ./$(BIN)


clean:
		rm -rf $(BIN)
		rm -rf libcalc.so