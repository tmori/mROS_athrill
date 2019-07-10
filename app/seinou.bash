#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 script"
    exit 1
fi

SEINOU_SCRIPT=${1}

PUB_TOPIC_DATA="This is a test data!"
PUB_TOPIC_NAME="test_string"
PUB_TOPIC_TYPE="std_msgs/String"

ROS_MASTER_PID=
function start_ros()
{
    roscore &
    ROS_MASTER_PID=${!}
    sleep 10
}

function stop_ros()
{
    kill -9 ${ROS_MASTER_PID}

    sleep 1

    ps aux | grep ros | grep -v grep  | awk '{print $2}' | xargs kill -9

}

function stop_athrill()
{
    ps aux | grep athrill | grep -v grep | awk '{print $2}' | xargs kill -9
}

function start_pubtopic()
{
    rostopic pub -r 1 ${PUB_TOPIC_NAME} ${PUB_TOPIC_TYPE} "${PUB_TOPIC_DATA}" &
    sleep 1
}

function start_atrhill()
{
    athrill-run-remote &
    sleep 2
}

start_ros

start_pubtopic

#athrill remote start
start_atrhill

bash  ${SEINOU_SCRIPT}

athrill_remote exit


stop_athrill
#break point setting


stop_ros



