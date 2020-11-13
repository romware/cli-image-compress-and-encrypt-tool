
CC :gcc
CFLAGS : -Wall -ansi -lm

all : sizeymcsizeface
sizeymcsizeface : sizeymcsizeface.o bitmap.o print.o encrypt.o compress.o filter.o user.o database.o 

sizeymcsizeface.o : sizeymcsizeface.c bitmap.o print.o encrypt.o compress.o filter.o user.o database.o bitmap.h print.h encrypt.h compress.h filter.h user.h database.h 

bitmap.o : bitmap.c bitmap.h

print.o : print.c print.h

encrypt.o : encrypt.c encrypt.h

compress.o : compress.c compress.h

filter.o : filter.c filter.h

user.o : user.c user.h

database.o : database.c database.h

clean :
	rm -f sizeymcsizeface sizeymcsizeface.o bitmap.o print.o encrypt.o compress.o filter.o user.o database.o
