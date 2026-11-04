#!/bin/bash

#/usr/local/bin/run

if [ -z "$1" ]; then
    echo "./run.sh <filename> or run <filename>"
    exit 1
fi

NAME="${1%.cpp}"

if [ ! -f "$NAME.cpp" ]; then
    echo "$NAME.cpp does not exist."
    exit 1
fi

g++ -std=c++17 -Wall "$NAME.cpp" -o "$NAME" && ./"$NAME"
