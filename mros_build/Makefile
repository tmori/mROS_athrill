ATHRILL_ROOT=../../../athrill
MROX_TARGET_DIR=../mros_target
MROS_LIB_DIR=../../../fork/mROS
MBED_LIB_DIR=../../../mros/asp-athrill-mbed/mbed-lib
PRJROOT_ETHERIF=$(MBED_LIB_DIR)/EthernetInterface
PRJROOT_MROS=$(MROS_LIB_DIR)/mros-lib
PRJROOT_ASP=../../../mros/asp-athrill-mbed/asp-athrill
SRC_ROOT=$(MROS_LIB_DIR)/mros-lib/mros-src
MROS_MSG_DIR=$(MROS_LIB_DIR)/mros-lib/mros-msgs
APL_DIR=../mros_ws/app

ROS_VERSION	:= kinetic

CDEFS += -DTARGET_ATHRILL 
CDEFS += -DLWIP_TRANSPORT_ETHERNET

TARGET	:= libmros.a

CC		:= gcc
CXX		:= g++
LINK	:= gcc
AR		:= ar

CXXFLAGS := -fno-use-cxa-atexit -fno-exceptions -fno-rtti 
CFLAGS	:= -O0 -g
CFLAGS	+= -gdwarf-2 -Wall -Wno-unused-label -Wpointer-arith   

IFLAGS	:= -I.
IFLAGS	+= -I$(MROX_TARGET_DIR)
IFLAGS	+= -I$(MROX_TARGET_DIR)/x86
IFLAGS	+= -I$(MROX_TARGET_DIR)/x86/os
IFLAGS	+= -I$(PRJROOT_ETHERIF)/lwip-athrill/include
IFLAGS	+= -I$(ATHRILL_ROOT)/trunk/apl/include

IFLAGS	+= -I$(SRC_ROOT)/inc
IFLAGS	+= -I$(SRC_ROOT)/config
IFLAGS	+= -I$(SRC_ROOT)/config/os/target/os_asp
IFLAGS	+= -I$(SRC_ROOT)/api
IFLAGS	+= -I$(SRC_ROOT)/protocol/cimpl
IFLAGS	+= -I$(SRC_ROOT)/node/cimpl
IFLAGS	+= -I$(SRC_ROOT)/topic/cimpl
IFLAGS	+= -I$(SRC_ROOT)/os/target/os_asp
IFLAGS	+= -I$(SRC_ROOT)/comm/cimpl/target/lwip
IFLAGS	+= -I$(SRC_ROOT)/comm/cimpl
IFLAGS	+= -I$(SRC_ROOT)/packet/cimpl
IFLAGS	+= -I$(SRC_ROOT)/packet/template/version/$(ROS_VERSION)
IFLAGS	+= -I$(SRC_ROOT)/packet/cimpl/version/$(ROS_VERSION)
IFLAGS	+= -I$(SRC_ROOT)/protocol/cimpl
IFLAGS	+= -I$(SRC_ROOT)/transfer/cimpl
IFLAGS	+= -I$(MROS_MSG_DIR)
IFLAGS	+= -I$(APL_DIR)/include

CXX_OBJ += ros_cimpl.o
CXX_OBJ += mros_comm_cimpl.o
CXX_OBJ += mros_comm_socket_cimpl.o
CXX_OBJ += mros_comm_tcp_client_cimpl.o
CXX_OBJ += mros_comm_tcp_client_factory_cimpl.o
CXX_OBJ += mros_comm_tcp_server_cimpl.o
CXX_OBJ += mros_memory.o
CXX_OBJ += mros_wait_queue.o
CXX_OBJ += mros_node_cimpl.o
CXX_OBJ += mros_exclusive_area.o
CXX_OBJ += mros_exclusive_ops_linux.o
CXX_OBJ += mros_os.o
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
CXX_OBJ += mros_os_config.o
CXX_OBJ += mros_usr_config.o
CXX_OBJ += mros_sys_config.o
CXX_OBJ += lwip_linux.o
CXX_OBJ += os_asp.o

OBJS	:= $(C_OBJ) $(CXX_OBJ)

VPATH	:= $(SRC_ROOT)/api
VPATH	+= $(SRC_ROOT)/comm/cimpl/target/lwip
VPATH	+= $(SRC_ROOT)/comm/cimpl/target/lwip
VPATH	+= $(SRC_ROOT)/comm/cimpl
VPATH	+= $(SRC_ROOT)/node/cimpl
VPATH	+= $(SRC_ROOT)/lib
VPATH	+= $(SRC_ROOT)/os
VPATH	+= $(SRC_ROOT)/os/target/os_asp
VPATH	+= $(SRC_ROOT)/packet/cimpl/version/$(ROS_VERSION)
VPATH	+= $(SRC_ROOT)/protocol/cimpl
VPATH	+= $(SRC_ROOT)/topic/cimpl
VPATH	+= $(SRC_ROOT)/transfer/cimpl
VPATH	+= $(SRC_ROOT)/config
VPATH	+= $(SRC_ROOT)/config/os/target/os_asp
VPATH	+= $(PRJROOT_MROS)
VPATH	+= $(MROX_TARGET_DIR)
VPATH	+= $(MROX_TARGET_DIR)/x86/lwip
VPATH	+= $(MROX_TARGET_DIR)/x86/os

main: libmros.a
	gcc $(IFLAGS)  $(CDEFS) $(CFLAGS) -o mros_test main.c -L. -lmros -lm -lpthread

%.o: %.S
	$(CC) -c $(IFLAGS)  $(CDEFS) $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(IFLAGS)  $(CDEFS) $(CFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(IFLAGS) $(CFLAGS) $(CDEFS) $(CXXFLAGS) $<

libmros.a: $(CXX_OBJ) $(C_OBJ)
	$(AR) -rcv  $(TARGET) $(CXX_OBJ) $(C_OBJ)

clean:
	rm -f *.o $(TARGET)
