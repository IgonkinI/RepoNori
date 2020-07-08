BIN := Calculator
SOURCES := main.c

.PHONY := clean
$(BIN): $(SOURCES)
		gcc -c library/*.c
		ar rc libcalc.a *.o
		cp libcalc.a /static
		rm -rf *.o
		gcc $(SOURCES) -L. -lcalc -o $(BIN)



clean:
		rm -rf $(BIN)
		rm -rf libcalc.a