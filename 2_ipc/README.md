# Interprocess communication

## Task: 
Write two programs, i.e., Program1.c, and Program2.c that communicate with each other through a shared memory. Both the programs must be run indefinitely. For each line of the input (e.g., a sequence of alphanumeric strings) entered for program 1, program2 should display the number of words and number of numerical digits of the input.

## Running instructions
* Open two terminals and navigate to the base folder '2_ipc'.
* In terminal 1, run the following command ```g++ -pipe -O2 -std=c++14 Program1.cpp -lm -o P1```.
* In terminal 2, run the following command ```g++ -pipe -O2 -std=c++14 Program2.cpp -lm -o P2```.
* Follow the instructions as shown in the terminal.
* To quit the program, press 'q'.