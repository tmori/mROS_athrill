#!/bin/bash

. ./seinou_comm.bash

START_BREAK_FILE="mros.cpp"
START_BREAK_LINE="459"

END_BREAK_FILE="app.cpp"
END_BREAK_LINE="49"

#check test condition
function_for_break_func main_task
athrill_remote p test_inner

#test point
athrill_remote b ${START_BREAK_FILE} ${START_BREAK_LINE}
athrill_remote b ${END_BREAK_FILE} ${END_BREAK_LINE}

#start test
wait_for_2break ${START_BREAK_FILE} ${START_BREAK_LINE} ${END_BREAK_FILE} ${END_BREAK_LINE}
echo ${S_ELAPS_VALUE} > seinou_result.txt
echo ${E_ELAPS_VALUE} >> seinou_result.txt
