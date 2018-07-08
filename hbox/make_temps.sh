#!/bin/sh

dd if=/dev/urandom of=logs/gshtest bs=1000000 count=1 2>/dev/null

dd if=/dev/urandom of=logs/gshtest2 bs=1000000 count=1 2>/dev/null

dd if=/dev/urandom of=logs/gshtest3 bs=1000000 count=1 2>/dev/null
