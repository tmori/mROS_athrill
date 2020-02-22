#ENV FOLDERS
ATHRILL_ROOT=../../../athrill
MROS_LIB_DIR=..
MBED_LIB_DIR=../../asp-athrill-mbed/mbed-lib
PRJROOT_ETHERIF=$(MBED_LIB_DIR)/EthernetInterface

include $(PRJROOT_ETHERIF)/Makefile.eif


TARGET	:= libmbed.a

IFLAGS	:= -I.
ifeq ($(mros_arch),arm)
include Makefile.arm
else
include Makefile.v850
endif

IFLAGS	+= $(INCLUDE_PATHS)
IFLAGS	+= -I$(PRJROOT_ETHERIF)/lwip-athrill/include
IFLAGS	+= -I$(MBED_LIB_DIR)/mbed-src/api
IFLAGS	+= -I$(PRJROOT_ASP)
IFLAGS	+= -I$(PRJROOT_ASP)/include
IFLAGS	+= -I$(PRJROOT_ASP)/arch
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