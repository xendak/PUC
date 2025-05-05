#!/bin/sh

clang -ggdb -Wall -lm -lraylib -lpthread -ldl -lrt ./main.c -o main

if [ "$1" = "run" ]; then
    exec ./main
fi
