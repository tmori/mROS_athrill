#ENV FOLDERS
ATHRILL_ROOT=../../../../athrill
MROS_LIB_DIR=..
MBED_LIB_DIR=../../../../mros/asp-athrill-mbed/mbed-lib
PRJROOT_ETHERIF=$(MBED_LIB_DIR)/EthernetInterface
PRJROOT_ASP=../../../../mros/asp-athrill-mbed//asp-athrill

include $(PRJROOT_ETHERIF)/Makefile.eif

TARGET	:= libmbed.a

CC		:= v850-elf-gcc
CXX		:= v850-elf-g++
LINK	:= v850-elf-gcc
AR		:= v850-elf-ar

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


OBJS	:= $(C_OBJ) $(CXX_OBJ)

VPATH	:= .
VPATH	+= $(PRJROOT_ETHERIF)
VPATH	+= $(PRJROOT_ETHERIF)/Socket
VPATH	+= $(PRJROOT_ETHERIF)/lwip-athrill


%.o: %.S
	$(CC) -c $(IFLAGS)  $(CDEFS) $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(IFLAGS)  $(CDEFS) $(CFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(IFLAGS) $(CFLAGS) $(CDEFS) $(CXXFLAGS) $<

all: $(CXX_OBJ) $(C_OBJ)
	$(AR) -rcv  $(TARGET) $(CXX_OBJ) $(C_OBJ)

clean:
	rm -f *.o $(TARGET)
