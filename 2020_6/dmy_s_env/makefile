SrcFiles= $(wildcard *.c)
DesFiles=$(patsubst %.c,%,$(SrcFiles))
all:$(DesFiles)

%:%.c	
	gcc -o $@ $<
