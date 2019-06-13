#include "test_serial.h"
#include "test_reg.h"
#include <string.h>
#include "athrill_syscall.h"
#include <math.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include "test_serial.h"
#include "primitive_container.h"
#include "mros_node.h"
#include "mros_topic.h"
#include "mros_topic_connector.h"
#include "mros_packet_decoder.h"
#include "mros_packet.h"

using namespace mros::lib;
using namespace mros::node;
using namespace mros::topic;
using namespace mros::topic::topology;
using namespace mros::memory;
using namespace mros::packet;

unsigned char stack_data[STACK_SIZE] __attribute__ ((section(".bss_noclr")));

sys_addr athrill_device_func_call __attribute__ ((section(".athrill_device_section")));


static void ros_node_test(void)
{
	mRosReturnType ret;
	RosNodeIdType id;

	ret = RosNode::init(2);
	test_print_line("RosNode::init(10)=", ret);

	ret = RosNode::create("tmori", ROS_NODE_TYPE_INNER, id);
	test_print_line("RosNode::create(tmori)=", ret);
	test_print_line("RosNode::create(id)=", id);

	ret = RosNode::remove("tmori");
	test_print_line("RosNode::remove(tmori)=", ret);

	ret = RosNode::create("Takashi", ROS_NODE_TYPE_OUTER, id);
	test_print_line("RosNode::create(Takashi)=", ret);
	test_print_line("RosNode::create(id)=", id);

	ret = RosNode::create("ABC", ROS_NODE_TYPE_INNER, id);
	test_print_line("RosNode::create(ABC)=", ret);
	test_print_line("RosNode::create(id)=", id);

	ret = RosNode::get("tmori", id);
	test_print_line("RosNode::get(tmori)=", ret);
	test_print_line("RosNode::get(id)=", id);

	ret = RosNode::get("Takashi", id);
	test_print_line("RosNode::get(Takashi)=", ret);
	test_print_line("RosNode::get(id)=", id);

	ret = RosNode::get("Mori", id);
	test_print_line("RosNode::get(Mori)=", ret);
	test_print_line("RosNode::get(id)=", id);
}

static void ros_topic_test(void)
{
	mRosReturnType ret;
	RosTopicIdType id;

	ret = RosTopic::init(2);
	test_print_line("RosTopic::init(2)=", ret);

	ret = RosTopic::create("tmori", id);
	test_print_line("RosTopic::create(tmori)=", ret);
	test_print_line("RosTopic::create(id)=", id);

	ret = RosTopic::remove("tmori");
	test_print_line("RosTopic::remove(tmori)=", ret);

	ret = RosTopic::create("Takashi", id);
	test_print_line("RosTopic::create(Takashi)=", ret);
	test_print_line("RosTopic::create(id)=", id);

	ret = RosTopic::create("ABC", id);
	test_print_line("RosTopic::create(ABC)=", ret);
	test_print_line("RosTopic::create(id)=", id);

	ret = RosTopic::get("tmori", id);
	test_print_line("RosTopic::get(tmori)=", ret);
	test_print_line("RosTopic::get(id)=", id);

	ret = RosTopic::get("Takashi", id);
	test_print_line("RosTopic::get(Takashi)=", ret);
	test_print_line("RosTopic::get(id)=", id);

	ret = RosTopic::get("Mori", id);
	test_print_line("RosTopic::get(Mori)=", ret);
	test_print_line("RosTopic::get(id)=", id);

	ret = RosTopic::get("ABC", id);
	test_print_line("RosTopic::get(ABC)=", ret);
	test_print_line("RosTopic::get(id)=", id);

}
static void ros_topic_memory_test(void)
{
	mRosReturnType ret;
	RosTopicIdType tid;
	mRosSizeType preallocation_count[MROS_MEMSIZE_NUM];

	ret = RosTopic::init(2);

	for (int i = 0; i < (int)MROS_MEMSIZE_NUM; i++) {
		preallocation_count[i] = 2;
	}
	mRosMemory mem_manager;

	ret = mem_manager.init(preallocation_count);
	test_print_line("mRosMemory::init(2)=", ret);

	ret = RosTopic::create("tmori", tid);
	test_print_line("RosTopic::create(tmori)=", ret);
	test_print_line("RosTopic::create(id)=", tid);

	mRosMemoryListEntryType *memory = NULL;
	ret = mem_manager.memory_alloc(17,  &memory);
	test_print_line("memory_alloc(17)=", ret);
	test_print_line("memory.memory_id=", memory->data.memory_id);
	test_print_line("memory.memsize_id=", memory->data.memsize_id);
	test_print_line("memory.memsize=", memory->data.memsize);

	ret = mem_manager.memory_free(*memory);
	test_print_line("memory_free(17)=", ret);

	ret = mem_manager.memory_alloc(17,  &memory);
	test_print_line("memory_alloc(17)=", ret);
	test_print_line("memory.memory_id=", memory->data.memory_id);
	test_print_line("memory.memsize_id=", memory->data.memsize_id);
	test_print_line("memory.memsize=", memory->data.memsize);

	ret = mem_manager.memory_free(*memory);
	test_print_line("memory_free(17)=", ret);

	memory->data.memp[0] = 't';
	memory->data.memp[1] = 'm';
	memory->data.memp[2] = 'o';
	memory->data.memp[3] = 'r';
	memory->data.memp[4] = 'i';
	memory->data.memp[5] = '\0';

	ret = RosTopic::add_data(tid, *memory);
	test_print_line("add_data=", ret);

	ret = RosTopic::add_data(tid, *memory);
	test_print_line("add_data=", ret);

	mRosMemoryListEntryType *ret_memory = NULL;
	ret = RosTopic::get_data(tid, &ret_memory);
	test_print_line("get_data=", ret);
	test_print_line("memory.memory_id=", ret_memory->data.memory_id);
	test_print_line("memory.memsize_id=", ret_memory->data.memsize_id);
	test_print_line("memory.memsize=", ret_memory->data.memsize);
	test_print_line(ret_memory->data.memp, ret);

	ret = mem_manager.memory_free(*ret_memory);
	test_print_line("memory_free(17)=", ret);

	ret = RosTopic::get_data(tid, &ret_memory);
	test_print_line("get_data=", ret);
}

static void ros_topic_connector_test(void)
{
	RosNodeIdType src;
	RosNodeIdType dst;
	RosFuncIdType func;
	RosTopicIdType id;
	PrimitiveContainer<RosTopicConnectorIdType> pub_container = PrimitiveContainer<RosTopicConnectorIdType>(10);
	PrimitiveContainer<RosTopicConnectorIdType> sub_container = PrimitiveContainer<RosTopicConnectorIdType>(10);

	mRosReturnType ret = RosTopicConnector::init(2, 2);
	test_print_line("RosTopicConnector::init(2)=", ret);

	ret = RosTopicConnector::get_pub_connectors(1, pub_container);
	test_print_line("get_connectors()=", ret);
	test_print_line("container.usecount=", pub_container.usecount);

	ret = RosTopic::init(2);
	test_print_line("RosTopic::init(2)=", ret);

	ret = RosNode::init(2);
	test_print_line("RosNode::init(2)=", ret);

	ret = RosNode::create("Mori", ROS_NODE_TYPE_INNER, src);
	test_print_line("RosNode::create(Mori)=", ret);
	test_print_line("RosNode::create(id)=", src);

	ret = RosNode::create("Takashi", ROS_NODE_TYPE_OUTER, dst);
	test_print_line("RosNode::create(Takashi)=", ret);
	test_print_line("RosNode::create(id)=", dst);

	ret = RosTopicConnector::add_pub("topic_A", src);
	test_print_line("add_pubnode_topic()=", ret);

	ret = RosTopicConnector::add_pub("topic_B", src);
	test_print_line("add_pubnode_topic()=", ret);

	ret = RosTopicConnector::add_pub("topic_C", src);
	test_print_line("add_pubnode_topic()=", ret);

	func = (RosFuncIdType)ros_topic_connector_test;
	ret = RosTopicConnector::add_sub("topic_A", dst, func);
	test_print_line("add_subnode_topic()=", ret);

	ret = RosTopic::get("topic_A", id);
	ret = RosTopicConnector::get_pub_connectors(id, pub_container);
	test_print_line("get_pub_connectors()=", ret);
	test_print_line("pub_container.usecount=", pub_container.usecount);

	ret = RosTopicConnector::get_sub_connectors(id, sub_container);
	test_print_line("get_sub_connectors()=", ret);
	test_print_line("sub_container.usecount=", sub_container.usecount);

	RosTopicConnectorType connector;

	ret = RosTopicConnector::get_pub(pub_container[0], connector);
	test_print_line("RosTopicConnector::get_pub()=", ret);
	test_print_line("connector.topic_id=", connector.topic_id);
	test_print_line("connector.node_id=", connector.node_id);
	test_print_line("connector.func_id=", connector.func_id);

	RosNodeType type;
	ret = RosNode::type(connector.node_id, type);
	test_print_line("RosNode::type()=", ret);
	test_print_line("src_type=", type);

	ret = RosTopicConnector::get_sub(pub_container[0], connector);
	test_print_line("RosTopicConnector::get_sub()=", ret);
	test_print_line("connector.topic_id=", connector.topic_id);
	test_print_line("connector.node_id=", connector.node_id);
	test_print_line("connector.func_id=", connector.func_id);

	ret = RosNode::type(connector.node_id, type);
	test_print_line("RosNode::type()=", ret);
	test_print_line("dst_type=", type);

	ret = RosTopicConnector::rel_pub_connectors(pub_container);
	test_print_line("rel_pub_connectors()=", ret);

	ret = RosTopicConnector::rel_sub_connectors(sub_container);
	test_print_line("rel_sub_connectors()=", ret);
}

static void ros_decoder(void)
{
	mRosReturnType ret;
	mros_uint32 port;
	mRosSizeType preallocation_count[MROS_MEMSIZE_NUM];
	for (int i = 0; i < (int)MROS_MEMSIZE_NUM; i++) {
		preallocation_count[i] = 2;
	}
	mRosMemory mem_manager;

	ret = mem_manager.init(preallocation_count);
	test_print_line("mRosMemory::init(2)=", ret);

	ret = mRosPacket::init(mem_manager);
	test_print_line("mRosPacket::init(2)=", ret);

	const char* test_string = "http://xxx.xxx.xx:8080/";
	mRosSizeType len = strlen(test_string) + 1U;
	mRosPacketType packet;

	ret = mRosPacket::get(packet, len);
	test_print_line("mRosPacket::get=", ret);

	memcpy(packet.data->data.memp, test_string, len - 1);
	packet.data->data.memp[len -1] = '\0';

	ret = mRosPacketDecoder::decode_port(port, packet);
	test_print_line("mRosPacketDecoder::decode_port=", ret);

	test_print_line("port=", port);



}

int main(void)
{
#if 0
	PrimitiveContainer<RosTopicConnectorIdType> container = PrimitiveContainer<RosTopicConnectorIdType>(10);
	RosTopicConnectorIdType i;

	for (i = 0; i < container.size(); i++) {
		container[i] = i;

		test_print_line("value=", container[i]);
	}
#endif

	//ros_topic_connector_test();
	//ros_topic_memory_test();
	ros_decoder();

	while (1) {
		;
	}
}
