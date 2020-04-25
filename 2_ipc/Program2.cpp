
#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>
using namespace std; 
  
int main() 
{ 
    // ftok is used to generate a unique key 
    key_t flag_key = ftok("./flagkey", 9); 
    // shmget returns an identifier in shmid 
    int flag_shmid = shmget(flag_key, 16, 0666|IPC_CREAT); 
    // shmat is used to attach to the shared memory 
    char *flag = (char*) shmat(flag_shmid, (void*)0, 0);

    // Create shared space for data reading
    key_t data_key = ftok("./data",10); 
    int data_shmid = shmget(data_key, 1024, 0666|IPC_CREAT); 
    char *data = (char*) shmat(data_shmid, (void*)0, 0);
    do{
        // Check if the current process to be run is P2.
        if(strcmp(flag, "2") == 0){
            string curData = data;
            // If the data provided is q, then quit the program
            if(strcmp(data, "q") == 0) {
                // Detach from shared memory
                shmdt(flag);
                shmdt(data);
                
                // Destroy the shared memory
                shmctl(flag_shmid,IPC_RMID,NULL); 
                shmctl(data_shmid,IPC_RMID,NULL); 
                return 0;
            }
            // Get the length of the data string
            int dataLen = curData.length();
            
            // Set alphabet and digit count to 0;
            int alphabet = 0;
            int number = 0;
            
            // Set !alphanum flag = true;
            int isalphaNum = true;
            for(int i = 0; i < dataLen; i++) {
                if(isalnum(curData[i])) {
                    // Increment alphabet count if alphabet
                    if (isalpha(curData[i])) alphabet++;
                    // Increment number count if digit
                    if (isdigit(curData[i])) number++;
                } else {
                    // Only alphanumeric strings allowed
                    std::cout << "Please enter only alphanumeric string." << std::endl << std::endl;
                    isalphaNum = false;
                    break;
                }
            }
            // Output
            if(isalphaNum) {
                std::cout << "\"" <<curData << "\"" << " has: " << std::endl;
                std::cout << "alphabets: " << alphabet << std::endl;
                std::cout << "digits: " << number << std::endl;
                std::cout << std::endl;
            }
            // Set the current process as P1
            sprintf(flag, "%s", "1");
        }
        
    }while(true);
    return 0; 
} 