#include <string.h> 
#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>
using namespace std; 
  
int main() 
{ 
    // ftok is used to generate a unique key 
    key_t flag_key = ftok("./flagkey", 9); 
    // shmget returns an identifier in shmid 
    int flag_shmid = shmget(flag_key, 16, 0666|IPC_CREAT); 
    // shmat is used to attach to the shared memory 
    char *flag = (char*) shmat(flag_shmid, (void*)0, 0);
    
    // Tell the shared space key that currently program 1 is running
    sprintf(flag, "%s", "1");

    // Create shared space for data reading
    key_t data_key = ftok("./data",10); 
    int data_shmid = shmget(data_key, 1024, 0666|IPC_CREAT); 
    char *data = (char*) shmat(data_shmid, (void*)0, 0);

    cout << "Press \'q\' to quit the program." << endl;
    do{
        cout.flush();
        // Check if current process to be run is P1 or not.
        while(strcmp(flag, "1") == 0){
            cout << "Enter data to be written: ";
            cin.getline(data, 100);
            std::cout.flush();
            // Set the current process as P2.
            sprintf(flag, "%s", "2");
            // If the input data is 1 then quit the program
            if(strcmp(data, "q") == 0) {
                // Detach from shared space memory
                shmdt(flag);
                shmdt(data); 
                return 0;
            }
        }
    }while(true);
    return 0; 
}