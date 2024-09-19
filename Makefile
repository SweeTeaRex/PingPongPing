PROG = project

CC = gcc
CFLAG = -Wall -g

${PROG}: ${PROG}.c 
	${CC} ${CFLAG} -o ${PROG} ${PROG}.c 

clean:
	rm ${PROG}