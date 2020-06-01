#!/bin/sh
g++ -Wall -Werror -O3 -o"eckert" -std=c++11 main.cpp com/*.cpp calc/*.cpp calc/engine/*.cpp calc/engine/proc/*.cpp calc/engine/proc/base/*.cpp calc/engine/proc/base/core/*.cpp calc/ncheck/*.cpp calc/util/*.cpp
