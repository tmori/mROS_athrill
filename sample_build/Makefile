#ENV FOLDERS
ATHRILL_ROOT=../../../athrill
MROS_LIB_DIR=..
MBED_LIB_DIR=../../asp-athrill-mbed/mbed-lib
PRJROOT_ETHERIF=$(MBED_LIB_DIR)/EthernetInterface
PRJROOT_MROS=$(MROS_LIB_DIR)/mros-lib
PRJROOT_ASP=../../asp-athrill-mbed//asp-athrill
PRJROOT_SAMPLE=${MROS_LIB_DIR}/sample_src

include $(PRJROOT_ETHERIF)/Makefile.eif
include $(PRJROOT_MROS)/Makefile.m

TARGET	:= sample

CC		:= v850-elf-gcc
CXX		:= v850-elf-g++
LINK	:= v850-elf-gcc

CXXFLAGS := -fno-use-cxa-atexit -fno-exceptions -fno-rtti 
CFLAGS	:= -O0 -mdisable-callt -mno-app-regs -mtda=0
CFLAGS	+= -gdwarf-2 -Wall -Wno-unused-label -Wpointer-arith  -mv850e2v3 -Wa,-mno-bcond17 -msoft-float -Wa,-mwarn-signed-overflow -Wa,-mwarn-unsigned-overflow

IFLAGS	:= -I.
IFLAGS	+= $(INCLUDE_PATHS)
IFLAGS	+= -I$(PRJROOT_ETHERIF)/lwip-athrill/include
IFLAGS	+= -I$(MBED_LIB_DIR)/mbed-src/api
IFLAGS	+= -I$(PRJROOT_ASP)
IFLAGS	+= -I$(PRJROOT_ASP)/include
IFLAGS	+= -I$(PRJROOT_ASP)/target/v850_gcc
IFLAGS	+= -I$(PRJROOT_ASP)/arch
IFLAGS	+= -I$(PRJROOT_ASP)/arch/v850_gcc
IFLAGS	+= -I$(ATHRILL_ROOT)/trunk/apl/include

CXX_OBJ += main.o
CXX_OBJ += xmlparser.o
CXX_OBJ += tcp_ros.o
CXX_OBJ += xmlcall.o
CXX_OBJ += ros.o
CXX_OBJ += mros.o

C_OBJ	+= start.o
C_OBJ	+= vector.o
C_OBJ	+= software_init.o
C_OBJ	+= interrupt.o
C_OBJ	+= interrupt_table.o
C_OBJ	+= timer.o
C_OBJ	+= interrupt_asm.o

OBJS	:= $(C_OBJ) $(CXX_OBJ)

VPATH	:= .
VPATH	+= $(PRJROOT_ETHERIF)
VPATH	+= $(PRJROOT_ETHERIF)/Socket
VPATH	+= $(PRJROOT_ETHERIF)/lwip-athrill
VPATH	+= $(PRJROOT_SAMPLE)
VPATH	+= $(PRJROOT_MROS)

LDSCRIPT = $(PRJROOT_SAMPLE)/v850.ld
LDFLAGS	:= -nostdlib -T $(LDSCRIPT)

LIBS := -lsupc++  -lstdc++  -lm -lc -lgcc


%.o: %.S
	$(CC) -c $(IFLAGS)  $(CDEFS) $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(IFLAGS)  $(CDEFS) $(CFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(IFLAGS) $(CFLAGS) $(CDEFS) $(CXXFLAGS) $<

all: $(CXX_OBJ) $(C_OBJ)
	$(LINK) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) -Wl,-Map,$(TARGET).map $(LIBS)

clean:
	rm -f *.o $(TARGET) $(TARGET).map