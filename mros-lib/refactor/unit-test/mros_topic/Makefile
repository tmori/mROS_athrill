ROOT_PATH	:= ../..

CC		:= g++

CFLAGS	:= -O0 
CFLAGS	+= -gdwarf-2 -Wall -Wno-unused-label -Wpointer-arith  

IFLAGS	+= -I$(ROOT_PATH)/src/inc
IFLAGS	+= -I$(ROOT_PATH)/src/api
IFLAGS	+= -I$(ROOT_PATH)/src/lib
IFLAGS	+= -I$(ROOT_PATH)/src/topic
IFLAGS	+= -I$(ROOT_PATH)/src/topic/cimpl
IFLAGS	+= -I$(ROOT_PATH)/src/node/cimpl
IFLAGS	+= -I$(ROOT_PATH)/src/transfer/cimpl
IFLAGS	+= -I$(ROOT_PATH)/src/config
IFLAGS	+= -I$(ROOT_PATH)/src/inc/target/asp
IFLAGS	+= -I$(ROOT_PATH)/src/inc/target/lwip

VPATH	:= $(ROOT_PATH)/src/lib
VPATH	+= $(ROOT_PATH)/src/api
VPATH	+= $(ROOT_PATH)/src/topic
VPATH	+= $(ROOT_PATH)/src/topic/cimpl
VPATH	+= $(ROOT_PATH)/src/node/cimpl
VPATH	+= $(ROOT_PATH)/src/transfer/cimpl


OBJS	:= mros_memory_impl.o
OBJS	+= ros.o
OBJS	+= mros_topic_impl.o
OBJS	+= mros_topic_cimpl.o
OBJS	+= mros_topic_connector_cimpl.o
OBJS	+= mros_topic_connector_factory_cimpl.o
OBJS	+= mros_node_cimpl.o
OBJS	+= mros_topic_data_publisher_cimpl.o
OBJS	+= mros_topic_data_subscriber_cimpl.o
OBJS	+= mros_os_stub.o

%.o: %.c
	$(CC) -c $(IFLAGS) $(CFLAGS) $<

%.o: %.cpp
	$(CC) -c $(IFLAGS) $(CFLAGS) $<


all: $(OBJS)
	gcc $(IFLAGS)  $(CFLAGS) mros_topic_test.cpp  $(OBJS) -lstdc++
	
clean:
	rm -f $(OBJS)