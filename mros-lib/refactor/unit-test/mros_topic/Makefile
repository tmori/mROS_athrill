ROOT_PATH	:= ../..

CFLAGS	:= -O0 
CFLAGS	+= -gdwarf-2 -Wall -Wno-unused-label -Wpointer-arith  

IFLAGS	+= -I$(ROOT_PATH)/src/inc
IFLAGS	+= -I$(ROOT_PATH)/src/lib
IFLAGS	+= -I$(ROOT_PATH)/src/topic
IFLAGS	+= -I$(ROOT_PATH)/src/topic/cimpl
IFLAGS	+= -I$(ROOT_PATH)/src/config

VPATH	:= $(ROOT_PATH)/src/lib
VPATH	+= $(ROOT_PATH)/src/topic
VPATH	+= $(ROOT_PATH)/src/topic/cimpl
VPATH	+= $(ROOT_PATH)/src/node/cimpl


OBJS	:= mros_memory_impl.o
OBJS	+= mros_topic_impl.o
OBJS	+= mros_topic_cimpl.o
OBJS	+= mros_topic_connector_cimpl.o
OBJS	+= mros_node_cimpl.o

%.o: %.c
	$(CC) -c $(IFLAGS) $(CFLAGS) $<

%.o: %.cpp
	$(CC) -c $(IFLAGS) $(CFLAGS) $<


all: $(OBJS)
	gcc $(IFLAGS)  $(CFLAGS) mros_topic_test.cpp  $(OBJS)
	
clean:
	rm -f $(OBJS)