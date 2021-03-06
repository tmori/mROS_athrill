#!/bin/bash

. ./seinou_comm.bash

START_BREAK_FILE="app.cpp"
START_BREAK_LINE="33"

END_BREAK_FILE="app.cpp"
END_BREAK_LINE="34"

#check test condition
function_for_break_func main_task
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
