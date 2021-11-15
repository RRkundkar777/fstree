#!/bin/bash

# Script to test the ms-tree program
makeDir()
{
    if [ ! -d tests]
    then 
        mkdir tests
    fi
}

# Creating log files
createLogs(){
    touch tests/ms-output.txt tests/ms-output.log;
    touch tests/std-output.txt tests/std-output.log;
}

# Getting output of program
getRawOutput(){
    ./ms-tree > tests/ms-output.txt;
    tree > tests/std-output.txt;
}

# Processing the output files
removeBlankLines()
{
    grep -v '^$' tests/ms-output.txt > tests/ms-output.log
    grep -v '^$' tests/std-output.txt > tests/std-output.log
}

# Removing additional spaces
removeTrailingSpaces()
{
    sed 's/[ \t]*$//' tests/ms-output.log > tests/tmp.log
    cp tests/tmp.log tests/ms-output.log
    rm tests/tmp.log    
}

# Removing foreign encoding chars
removeIllegalChars()
{
    sed -i 's/  /  /g' tests/std-output.log
}

# Replacing individual chars
replaceInvalidChars()
{
    sed -i 's/└/├/g' tests/std-output.log
}

# Displaying the test output
recordOutput()
{
    diff tests/ms-output.log tests/std-output.log > tests/result.log
    
    if [ -s tests/result.log ]
    then
        echo "Test Failed"
    else
        echo "Test Passed"
    fi
}

# Clearing the dumps
clearDumps()
{
    rm tests/*.log
    rm tests/*.txt
}

# Driver Code
main()
{
    createLogs
    getRawOutput
    removeBlankLines
    removeTrailingSpaces
    removeIllegalChars
    replaceInvalidChars
    recordOutput
    clearDumps
}

main