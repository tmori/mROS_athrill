#!/bin/bash

cd ../../mbed_build

if [ $# -eq 0 ]
then
	make
else
	make clean;make
fi
