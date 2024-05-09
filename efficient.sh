#!/bin/bash
g++ efficient.cpp -o efficient
./efficient "$1" "$2" 
./efficient.out "$1" "$2" 