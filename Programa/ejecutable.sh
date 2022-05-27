#!/bin/bash

gcc -o ejecutable -fopenmp menu.c matrix.c metrics.c pi.c -lm
./ejecutable
