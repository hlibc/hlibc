#!/bin/sh

dd if=/dev/urandom of=logs/gshtest bs=1 count=1000000 2>logfile

dd if=/dev/urandom of=logs/gshtest2 bs=1 count=1000000 2>logfile

dd if=/dev/urandom of=logs/gshtest3 bs=1 count=1000000 2>logfile
