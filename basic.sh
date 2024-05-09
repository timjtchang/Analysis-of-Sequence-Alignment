#!/bin/bash
g++ basic.cpp -o basic
./basic "$1" "$2" 
./basic.out "$1" "$2"