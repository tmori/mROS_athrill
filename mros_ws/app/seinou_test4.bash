#!/bin/bash

. ./seinou_comm.bash

START_BREAK_FILE="app.cpp"
START_BREAK_LINE="39"

END_BREAK_FILE="app.cpp"
END_BREAK_LINE="40"

#set test condition
function_for_break_func main_task
TEST_VAL_ADDR=`nm -l asp | grep test_inner | awk '{print $1}'`
athrill_remote s 0x${TEST_VAL_ADDR} 1
athrill_remote p test_inner

#test point
athrill_remote b ${START_BREAK_FILE} ${START_BREAK_LINE}
athrill_remote b ${END_BREAK_FILE} ${END_BREAK_LINE}

#start test
wait_for_break ${START_BREAK_FILE} ${START_BREAK_LINE}
get_elaps
echo ${ELAPS_VALUE} > seinou_result.txt

wait_for_break ${END_BREAK_FILE} ${END_BREAK_LINE}
get_elaps
echo ${ELAPS_VALUE} >> seinou_result.txt
