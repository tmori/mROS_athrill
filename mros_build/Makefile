#ENV FOLDERS
ATHRILL_ROOT=../../../../athrill
MROS_LIB_DIR=..
MBED_LIB_DIR=../../../../mros/asp-athrill-mbed/mbed-lib
PRJROOT_ETHERIF=$(MBED_LIB_DIR)/EthernetInterface
PRJROOT_MROS=$(MROS_LIB_DIR)/mros-lib
PRJROOT_ASP=../../../../mros/asp-athrill-mbed/asp-athrill
SRC_ROOT=$(MROS_LIB_DIR)/mros-lib/src

INCLUDE_PATHS += \
  		 -I$(MBED_LIB_DIR)/EthernetInterface/lwip \
  		 -I$(MBED_LIB_DIR)/EthernetInterface/lwip-sys \
 		 -I$(MBED_LIB_DIR)/EthernetInterface/lwip/include \
 		 -I$(MBED_LIB_DIR)/EthernetInterface/lwip/include/ipv4 
CDEFS += -DTARGET_ATHRILL
CDEFS += -DLWIP_TRANSPORT_ETHERNET

TARGET	:= libmros.a

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

IFLAGS	+= -I$(SRC_ROOT)/inc
IFLAGS	+= -I$(SRC_ROOT)/config
IFLAGS	+= -I$(SRC_ROOT)/api
IFLAGS	+= -I$(SRC_ROOT)/protocol/cimpl
IFLAGS	+= -I$(SRC_ROOT)/node/cimpl
IFLAGS	+= -I$(SRC_ROOT)/topic/cimpl
IFLAGS	+= -I$(SRC_ROOT)/os/target/asp
IFLAGS	+= -I$(SRC_ROOT)/comm/cimpl/target/lwip
IFLAGS	+= -I$(SRC_ROOT)/comm/cimpl
IFLAGS	+= -I$(SRC_ROOT)/packet/cimpl
IFLAGS	+= -I$(SRC_ROOT)/packet/template
IFLAGS	+= -I$(SRC_ROOT)/protocol/cimpl
IFLAGS	+= -I$(SRC_ROOT)/transfer/cimpl

CXX_OBJ += ros.o
CXX_OBJ += mros_comm_cimpl.o
CXX_OBJ += mros_comm_socket_cimpl.o
CXX_OBJ += mros_comm_tcp_client_cimpl.o
CXX_OBJ += mros_comm_tcp_client_factory_cimpl.o
CXX_OBJ += mros_comm_tcp_server_cimpl.o
CXX_OBJ += mros_memory.o
CXX_OBJ += mros_wait_queue.o
CXX_OBJ += mros_node_cimpl.o
CXX_OBJ += mros_exclusive_area.o
CXX_OBJ += mros_exclusive_ops.o
CXX_OBJ += mros_os.o
CXX_OBJ += mros_packet_cimpl.o
CXX_OBJ += mros_packet_decoder_cimpl.o
CXX_OBJ += mros_packet_encoder_cimpl.o
CXX_OBJ += mros_protocol_client_rpc_cimpl.o
CXX_OBJ += mros_protocol_master_cimpl.o
CXX_OBJ += mros_protocol_operation_cimpl.o
CXX_OBJ += mros_protocol_publish_cimpl.o
CXX_OBJ += mros_protocol_server_proc_cimpl.o
CXX_OBJ += mros_protocol_slave_cimpl.o
CXX_OBJ += mros_protocol_subscribe_cimpl.o
CXX_OBJ += mros_topic_data_publisher_cimpl.o
CXX_OBJ += mros_topic_data_subscriber_cimpl.o
CXX_OBJ += mros_topic_cimpl.o
CXX_OBJ += mros_topic_connector_cimpl.o
CXX_OBJ += mros_topic_connector_factory_cimpl.o
CXX_OBJ += mros_name.o

OBJS	:= $(C_OBJ) $(CXX_OBJ)

VPATH	:= $(SRC_ROOT)/api
VPATH	+= $(SRC_ROOT)/comm/cimpl/target/lwip
VPATH	+= $(SRC_ROOT)/comm/cimpl/target/lwip
VPATH	+= $(SRC_ROOT)/comm/cimpl
VPATH	+= $(SRC_ROOT)/node/cimpl
VPATH	+= $(SRC_ROOT)/lib
VPATH	+= $(SRC_ROOT)/os
VPATH	+= $(SRC_ROOT)/os/target/asp
VPATH	+= $(SRC_ROOT)/packet/cimpl
VPATH	+= $(SRC_ROOT)/protocol/cimpl
VPATH	+= $(SRC_ROOT)/topic/cimpl
VPATH	+= $(SRC_ROOT)/transfer/cimpl
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
