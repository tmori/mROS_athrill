#!/bin/bash

export LD_LIBRARY_PATH=/usr/local/athrill-gcc:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=/usr/local/athrill-gcc/v850-elf/lib:${LD_LIBRARY_PATH}
export PATH=/usr/local/athrill-gcc/bin/:${PATH}

cd ${1}
make
