#include <iostream>
#include <string>
#include <bits/stdc++.h>           
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

void pwd() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    cout << "$ ";
}

void ls()
{
	DIR *Dir;
    char cwd[1024];
    struct dirent *DirEntry;
    getcwd(cwd, sizeof(cwd));
    Dir = opendir(cwd);

    while(DirEntry=readdir(Dir))
    {
        cout << DirEntry -> d_name << endl;
   }
   cout << "$ ";
} 

void mkdir()
{
    char dir_name[1024];
    cin >> dir_name;
    mkdir(dir_name, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
    cout << "directory created successfully" << endl;
    cout << "$ ";
}

void rmdir()
{
    char dir_name[1024];
    cin >> dir_name;
    remove(dir_name);
    cout << "directory removed successfully" << endl;
    cout << "$ ";
}

void rm()
{
    char file_name[1024];
    cin >> file_name;
    remove(file_name);
    cout << "file removed successfully" << endl;
    cout << "$ ";
}

void cd()
{
    char dir_name[1024];
    cin >> dir_name;
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    chdir(dir_name);
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    cout << "$ ";
}

int openterm() {
    string ip;
    vector<string> instr;
    while(ip != "exit") {
        cout << "$ ";
        cin >> ip;
        if(!(ip.compare("pwd"))){
            int process_pwd = fork();
            if(process_pwd == 0){
                pwd();
                exit(0);
            }
        }
        if(!(ip.compare("ls"))){
            int process_ls = fork();
            if(process_ls == 0){
                ls();
                exit(0);
            }
        }
        if(!(ip.compare("mkdir"))){
            int process_mkdir = fork();
            if(process_mkdir == 0){
                mkdir();
                exit(0);
            }
        }
        if(!(ip.compare("rmdir"))){
            int process_rmdir = fork();
            if(process_rmdir == 0){
                rmdir();
                exit(0);
            }
        }
        if(!(ip.compare("rm"))){
            int process_rm = fork();
            if(process_rm == 0){
                rm();
                exit(0);
            }
        }
        if(!(ip.compare("cd"))){
            int process_cd = fork();
            if(process_cd == 0){
                cd();
                exit(0);
            }
        }
    } 
    std::cout << "Exiting the terminal." << std::endl; 
    exit(0);
    return 0;  
}

int main() {
    char ch;
    std::cout << "Enter [y] to start terminal: ";
    std::cin >> ch;
    
    if(ch == 'y') {
        std::cout << "Starting terminal, enter [quit] to terminate." << std::endl;
        return openterm();
    }
}