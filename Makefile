VAR = ${patsubst %c,%o,${wildcard *.c}}
a.out: $(VAR)
	gcc -o $@ $^
clean:
	rm *.o *.out