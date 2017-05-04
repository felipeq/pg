#!/bin/bash
x=0.5
for ((e=1; $e <=15; e++)) ;
do
	./a.out $x $e
done
