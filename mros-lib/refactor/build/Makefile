ROOT_PATH 		:= ..
APL_DIR		:= ../../../../../../athrill/trunk/apl
ATHRILL_ROOT	:= ../../../../../../athrill/trunk/src
BUILD_PATH		:= .
CPU_CONFIG_PATH	:= $(ATHRILL_ROOT)/config/target/v850esfk3


TARGET	:= test_main.elf

CC		:= v850-elf-gcc
CXX		:= v850-elf-g++

LINK	:= v850-elf-gcc

OBJS	:= start.o
OBJS	+= vector.o
OBJS	+= interrupt.o
OBJS	+= interrupt_table.o
OBJS	+= timer.o
OBJS	+= interrupt_asm.o
OBJS	+= software_init.o
OBJS	+= mros_topic_connector_impl.o
OBJS	+= mros_topic_impl.o
OBJS	+= mros_node_impl.o
OBJS	+= mros_memory_impl.o
OBJS	+= mros_packet_impl.o
OBJS	+= mros_packet_encoder_impl.o
OBJS	+= mros_packet_decoder_impl.o
OBJS	+= mros_topic_data_publisher_impl.o
OBJS	+= main.o

CXXFLAGS := -fno-use-cxa-atexit -fno-exceptions -fno-rtti 
CFLAGS	:= -O0 -mdisable-callt -mno-app-regs -mtda=0
CFLAGS	+= -gdwarf-2 -Wall -Wno-unused-label -Wpointer-arith  -mv850e2v3 -Wa,-mno-bcond17 -msoft-float -Wa,-mwarn-signed-overflow -Wa,-mwarn-unsigned-overflow


LDSCRIPT = $(ROOT_PATH)/baremetal/v850esfk3.ld
LDFLAGS	:= -nostdlib -T $(LDSCRIPT)

TEST_PATH := .

IFLAGS	:= -I.
IFLAGS	+= -I$(ROOT_PATH)/baremetal
IFLAGS	+= -I$(CPU_CONFIG_PATH)
IFLAGS	+= -I$(APL_DIR)/include

IFLAGS	+= -I$(ROOT_PATH)/src/lib
IFLAGS	+= -I$(ROOT_PATH)/src/inc
IFLAGS	+= -I$(ROOT_PATH)/src/node
IFLAGS	+= -I$(ROOT_PATH)/src/topic
IFLAGS	+= -I$(ROOT_PATH)/src/transfer
IFLAGS	+= -I$(ROOT_PATH)/src/packet
IFLAGS	+= -I$(ROOT_PATH)/src/packet/template

VPATH	:= $(ROOT_PATH)/baremetal
VPATH	+= $(ROOT_PATH)/src/lib
VPATH	+= $(ROOT_PATH)/src/topic
VPATH	+= $(ROOT_PATH)/src/node
VPATH	+= $(ROOT_PATH)/src/packet
VPATH	+= $(ROOT_PATH)/src/transfer
VPATH	+= $(TEST_PATH)

LIBS := -lsupc++  -lstdc++  -lm -lc -lgcc  libathrillc.o


%.o: %.S
	$(CC) -c $(IFLAGS) $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(IFLAGS) $(CFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(IFLAGS) $(CFLAGS) $(CXXFLAGS) $<

all: $(OBJS)
	v850-elf-gcc -c $(IFLAGS) $(CFLAGS) libathrillc.c
	$(LINK) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) -Wl,-Map,$(TARGET).map $(LIBS)
	v850-elf-objdump -d $(TARGET) > $(TARGET).dump



clean:
	rm -f $(OBJS) $(TARGET) libathrillc.o *.map
