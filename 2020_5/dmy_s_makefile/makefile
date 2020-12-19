#get all .c files
SrcFiles=$(wildcard *.c)
#all .c files --> .o files
ObjFiles1=$(patsubst %.c,%.o,$(SrcFiles))
#ObjFiles=main.o add.o sub.o
dmy_app:$(ObjFiles1)
	gcc -o dmy_app -I ./dmy_include $(ObjFiles1)
%.o:%.c
	gcc -c $< -I./dmy_include -o $@
test:
	echo $(SrcFiles)
	echo $(ObjFiles1)

.PHONY:clean

clean:
	-@rm -f *.o
	rm -f dmy_app
