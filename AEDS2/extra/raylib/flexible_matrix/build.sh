#!/bin/sh

clang -ggdb -Wall -lm -lraylib -lpthread -ldl -lrt -lX11 ./main.c -o main

if [ "$1" = "run" ]; then
    exec ./main
fi
