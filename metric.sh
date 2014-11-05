#!/bin/sh 

find src include test -iname "*.cpp" -o -iname "*.hpp" | cccc --lang=c++ -
