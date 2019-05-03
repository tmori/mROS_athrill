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

using namespace mros::lib;

unsigned char stack_data[STACK_SIZE] __attribute__ ((section(".bss_noclr")));

sys_addr athrill_device_func_call __attribute__ ((section(".athrill_device_section")));


int main(void)
{
	PrimitiveContainer<RosTopicConnectorIdType> container = PrimitiveContainer<RosTopicConnectorIdType>(10);
	RosTopicConnectorIdType i;

	for (i = 0; i < container.size(); i++) {
		container[i] = i;

		test_print_line("value=", container[i]);
	}

	while (1) {
		;
	}
}
