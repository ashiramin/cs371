CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I.
LIBS = -lpthread -ldl
SRCS = p2.c
OBJS = p2.o
EXE = server

all:	$(EXE)

$(EXE):	$(OBJS) 
	$(CC) -o $(EXE) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(EXE)
