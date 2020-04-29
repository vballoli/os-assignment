#!/bin/bash

if [ "$1" == "1" ]; then
    echo
    echo "----- Executing question 1: Shell -----"
    echo
    cd 1_shell/
    g++ terminal.cpp -o terminal -std=c++11 && ./terminal
elif [ "$1" == "2" ]; then
    echo
    echo "----- Executing question 2: Interprocess Communication -----"
    echo
    echo "### Question 2 not supported through this execute file ###"
    echo "### Refer to sub folder '2_ipc' for run instructions ###"
    echo

elif [ "$1" == "3" ]; then
    echo
    echo "----- Executing question 3: CPU Process Scheduling -----"
    echo
    cd 3_proc_scheduling/
    bash run.sh
elif [ "$1" == "4" ]; then
    echo
    echo "----- Executing question 4: Multithreading -----"
    echo
    cd 4_multithreading/
    if [ "$2" == "print_pids" ]; then
        g++ -std=c++11 -pthread -o multithreading main.cpp && ./multithreading print_pids
    else
        g++ -std=c++11 -pthread -o multithreading main.cpp && ./multithreading
    fi
fi