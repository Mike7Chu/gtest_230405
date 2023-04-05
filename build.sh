#!/bin/sh
g++ $1 -lgtest -L. -I./googletest/googletest/include/ -pthread