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

unsigned char stack_data[STACK_SIZE] __attribute__ ((section(".bss_noclr")));

sys_addr athrill_device_func_call __attribute__ ((section(".athrill_device_section")));


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
	while (1) {
		;
	}
}
