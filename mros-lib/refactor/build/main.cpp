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

using namespace mros::lib;
using namespace mros::node;
using namespace mros::topic;
using namespace mros::topic::topology;
using namespace mros::memory;

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
	PrimitiveContainer<RosTopicConnectorIdType> container = PrimitiveContainer<RosTopicConnectorIdType>(10);

	mRosReturnType ret = RosTopicConnector::init(2);
	test_print_line("RosTopicConnector::init(2)=", ret);

	ret = RosTopicConnector::get_connectors(1, container);
	test_print_line("get_connectors()=", ret);
	test_print_line("container.usecount=", container.usecount);

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

	ret = RosTopicConnector::add_pubnode_topic("topic_A", src);
	test_print_line("add_pubnode_topic()=", ret);

	ret = RosTopicConnector::add_pubnode_topic("topic_B", src);
	test_print_line("add_pubnode_topic()=", ret);

	ret = RosTopicConnector::add_pubnode_topic("topic_C", src);
	test_print_line("add_pubnode_topic()=", ret);

	func = (RosFuncIdType)ros_topic_connector_test;
	ret = RosTopicConnector::add_subnode_topic("topic_A", dst, func);
	test_print_line("add_subnode_topic()=", ret);

	ret = RosTopic::get("topic_A", id);
	ret = RosTopicConnector::get_connectors(id, container);
	test_print_line("get_connectors()=", ret);
	test_print_line("container.usecount=", container.usecount);

	RosTopicConnectorType connector;

	ret = RosTopicConnector::get(container[0], connector);
	test_print_line("RosTopicConnector::get()=", ret);
	test_print_line("connector.topic_id=", connector.topic_id);
	test_print_line("connector.src_id=", connector.src_id);
	test_print_line("connector.dst_id=", connector.dst_id);
	test_print_line("connector.func_id=", connector.func_id);

	RosNodeType type;
	ret = RosNode::type(connector.src_id, type);
	test_print_line("RosNode::type()=", ret);
	test_print_line("src_type=", type);

	ret = RosNode::type(connector.dst_id, type);
	test_print_line("RosNode::type()=", ret);
	test_print_line("dst_type=", type);

	ret = RosTopicConnector::rel_connectors(container);
	test_print_line("rel_connectors()=", ret);
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
	ros_topic_memory_test();

	while (1) {
		;
	}
}
