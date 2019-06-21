ROOT_PATH	:= ../..

CFLAGS	:= -O0 
CFLAGS	+= -gdwarf-2 -Wall -Wno-unused-label -Wpointer-arith  

IFLAGS	+= -I$(ROOT_PATH)/src/inc
IFLAGS	+= -I$(ROOT_PATH)/src/lib

VPATH	:= $(ROOT_PATH)/src/lib


OBJS	:= mros_memory_impl.o

%.o: %.c
	$(CC) -c $(IFLAGS) $(CFLAGS) $<


all: $(OBJS)
	gcc $(IFLAGS)  $(CFLAGS) mros_memory_test.c  $(OBJS)
	
clean:
	rm -f $(OBJS)