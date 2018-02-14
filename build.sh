#!/bin/sh

set -e

for f in *.c
do
	gcc -o $(basename -s .c $f) $f
done
