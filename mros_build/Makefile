#ENV FOLDERS
ATHRILL_ROOT=../../../athrill
MROS_LIB_DIR=..
MBED_LIB_DIR=../../asp-athrill-mbed/mbed-lib
PRJROOT_ETHERIF=$(MBED_LIB_DIR)/EthernetInterface
PRJROOT_MROS=$(MROS_LIB_DIR)/mros-lib

INCLUDE_PATHS += -I$(MBED_LIB_DIR)/EthernetInterface \
		 -I$(MBED_LIB_DIR)/EthernetInterface/Socket \
  		 -I$(MBED_LIB_DIR)/EthernetInterface/lwip \
  		 -I$(MBED_LIB_DIR)/EthernetInterface/lwip-sys \
 		 -I$(MBED_LIB_DIR)/EthernetInterface/lwip/include \
 		 -I$(MBED_LIB_DIR)/EthernetInterface/lwip/include/ipv4 
CDEFS += -DTARGET_ATHRILL
CDEFS += -DLWIP_TRANSPORT_ETHERNET

TARGET	:= libmros.a


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

CXX_OBJ += xmlparser.o
CXX_OBJ += tcp_ros.o
CXX_OBJ += xmlcall.o
CXX_OBJ += ros.o
CXX_OBJ += mros.o

OBJS	:= $(C_OBJ) $(CXX_OBJ)

VPATH	:= .
VPATH	+= $(PRJROOT_MROS)

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