all: bof

bof: bof.c
	gcc -g -D_FORTIFY_SOURCE=0 -fno-stack-protector -o $@ $^
    
clean:
	rm bof
    
