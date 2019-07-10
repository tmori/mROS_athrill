#!/bin/bash

function wait_for_break()
{
    filename=${1}
    lineno=${2}

    while [ 1 ]
    do
        RET_VALUE=`athrill_remote c`
        FILE=`echo ${RET_VALUE} | awk '{print $1}'`
        LINE=`echo ${RET_VALUE} | awk '{print $2}'`

        if [ $FILE = ${filename} -a ${LINE} = ${lineno} ]
        then
            break;
        fi
    done
}

function_for_break_func()
{
    funcname=${1}
    athrill_remote b ${funcname}
    athrill_remote c
}

ELAPS_VALUE=
function get_elaps()
{
    ELAPS_VALUE=`athrill_remote e | awk '{print $2}'`
}

S_ELAPS_VALUE=
E_ELAPS_VALUE=
function wait_for_2break()
{
    s_filename=${1}
    s_lineno=${2}
    e_filename=${3}
    e_lineno=${4}

    S_ELAPS_VALUE="NONE"
    E_ELAPS_VALUE="NONE"
    while [ 1 ]
    do
        RET_VALUE=`athrill_remote c`
        FILE=`echo ${RET_VALUE} | awk '{print $1}'`
        LINE=`echo ${RET_VALUE} | awk '{print $2}'`

        if [ ${FILE} = ${s_filename} -a ${LINE} = ${s_lineno} ]
        then
            get_elaps
            S_ELAPS_VALUE=${ELAPS_VALUE}
            E_ELAPS_VALUE="NONE"
            #wait for data receive from publisher
            #not to count tcp comm elaps. 
            sleep 2
        elif [ ${FILE} = ${e_filename} -a ${LINE} = ${e_lineno} ]
        then
            get_elaps
            E_ELAPS_VALUE=${ELAPS_VALUE}
        else
            continue
        fi

        if [ ${S_ELAPS_VALUE} = "NONE" -o ${E_ELAPS_VALUE} = "NONE" ]
        then
            continue
        fi

        break;
    done
}