#! /usr/bin/bash

set -xe

nasm -f elf fizzbuzz.asm -o fizzbuzz.o
ld -m elf_i386 fizzbuzz.o
