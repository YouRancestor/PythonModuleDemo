#!/bin/bash

if [ -z "${PYTHON_INC_PATH}" ];then
    echo "usage:"
    echo "PYTHON_INC_PATH=/dir/to/Python.h PYTHON_LIB_PATH=/dir/to/libpython3.so ./build [Debug]"
    echo "未设置 PYTHON_INC_PATH"
    echo "PYTHON_INC_PATH: Python.h 所在目录"
    exit
fi

if [ -z "${PYTHON_LIB_PATH}" ];then
    echo "usage:"
    echo "PYTHON_INC_PATH=/dir/to/Python.h PYTHON_LIB_PATH=/dir/to/libpython3.so ./build [Debug]"
    echo "未设置 PYTHON_LIB_PATH"
    echo "PYTHON_LIB_PATH: libpython3.so 所在目录"
    exit
fi

if [ "$1" = "Debug" ];then
    flag="-O0 -g"
else
    flag="-O3 -DNDEBUG"
fi


g++ -I${PYTHON_INC_PATH} -c test.cpp -o test.o -fPIC $flag
g++ -shared test.o -L${PYTHON_LIB_PATH} -lpython3 -o xx.so
