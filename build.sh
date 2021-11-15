#! /bin/bash

# 111903073 Rushikesh Rameshwar Kundkar
# 111903077 Sagar Gulab Patil

# Script to build the code

# Compilation
gcc -c main.c 
gcc -c tree.c

# Output generation
gcc main.o tree.o -o ms-tree

# Removal of dumps
rm *.o