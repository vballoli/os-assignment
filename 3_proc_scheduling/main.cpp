#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Process {
    string pid;
    int arrival_time;
    int burst_time;
    int priority;

    Process(string pid_, int arrival_time_, int burst_time_, int priority_) 
    {
        pid = pid_;
        arrival_time = arrival_time_;
        burst_time = burst_time_;
        priority = priority_;
    }
};

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

void construct_queue(string filename, vector<Process> &processes) {
    ifstream file(filename);
    string process;
    while(getline(file, process)) {
        vector<string> p_info = split(process, ',');
        struct Process p = Process(p_info[0], stoi(p_info[1]), stoi(p_info[2]), stoi(p_info[3]));
        processes.push_back(p);
    }
}

class FCFS
{
    private:
        vector<Process> processes;
        vector<Process> modified_processes;
    public:
        FCFS(vector<Process> &processes) {
            copy(processes.begin(), processes.end(), back_inserter(this->processes));
            copy(processes.begin(), processes.end(), back_inserter(this->modified_processes));
        }

    static bool compare(Process p1, Process p2) {
        if(p1.arrival_time != p2.arrival_time)
        return p1.arrival_time < p2.arrival_time;
        else return p1.burst_time < p2.burst_time;
    }

    void setup() {
        sort(modified_processes.begin(), modified_processes.end(), compare);
        for(int i=0; i<5; i++) cout<<modified_processes[i].pid<<" ";
        cout<<endl;
    }

    void getWaitingTimes(vector<int> &waiting_times) {
        this->setup();
        vector<int> service_time(waiting_times.size(), 0);
        service_time[0] = modified_processes[0].arrival_time;
        waiting_times[0] = 0;

        for(int i=1; i<waiting_times.size(); i++) {
            service_time[i] = service_time[i-1] + modified_processes[i-1].burst_time;
            waiting_times[i] = service_time[i] - modified_processes[i].arrival_time;  
            if (waiting_times[i] < 0) waiting_times[i] = 0; 
        }
    }

    void getTurnaroundTimes(vector<int> &waiting_times, vector<int> &turnaround_times) {
        for (int i=0; i<waiting_times.size(); i++) 
        turnaround_times[i] = waiting_times[i] + modified_processes[i].burst_time;
    }

};

class Priority
{
    private:
        vector<Process> processes;
        vector<Process> modified_processes;
    public:
        Priority(vector<Process> &processes) {
            copy(processes.begin(), processes.end(), back_inserter(this->processes));
            copy(processes.begin(), processes.end(), back_inserter(this->modified_processes));
        }

        static bool compare(Process p1, Process p2) {
            if(p1.arrival_time == p2.arrival_time) return p1.priority > p2.priority;
            else return p1.arrival_time < p2.arrival_time;
        }

        void setup() {
            sort(modified_processes.begin(), modified_processes.end(), compare);
            for(int i=0; i<5; i++) cout<<modified_processes[i].pid<<" ";
            cout<<endl;
        }

        void getWaitingTimes(vector<int> &waiting_times) {
            this->setup();
            vector<int> service_time(waiting_times.size(), 0);
            service_time[0] = modified_processes[0].arrival_time;
            waiting_times[0] = 0;

            for(int i=1; i<waiting_times.size(); i++) {
                service_time[i] = service_time[i-1] + modified_processes[i-1].burst_time;
                waiting_times[i] = service_time[i] - modified_processes[i].arrival_time;  
                if (waiting_times[i] < 0) waiting_times[i] = 0; 
            }
        }

        void getTurnaroundTimes(vector<int> &waiting_times, vector<int> &turnaround_times) {
            for (int i=0; i<waiting_times.size(); i++) 
            turnaround_times[i] = waiting_times[i] + modified_processes[i].burst_time;
        }

};


int main() {
    vector<Process> processes;
    construct_queue("processes.txt", processes);
    
    FCFS f(processes);
    vector<int> waiting_times(processes.size(), 0);
    vector<int> turnaround_times(processes.size(), 0);
    f.getWaitingTimes(waiting_times);
    f.getTurnaroundTimes(waiting_times, turnaround_times);

    for(int i=0; i<5; i++) cout<<waiting_times[i]<<" ";
    cout<<endl;
    for(int i=0; i<5; i++) cout<<turnaround_times[i]<<" ";
    cout<<endl;

    Priority p(processes);
    vector<int> waiting_times_p(processes.size(), 0);
    vector<int> turnaround_times_p(processes.size(), 0);
    p.getWaitingTimes(waiting_times_p);
    p.getTurnaroundTimes(waiting_times_p, turnaround_times_p);

    for(int i=0; i<5; i++) cout<<waiting_times_p[i]<<" ";
    cout<<endl;
    for(int i=0; i<5; i++) cout<<turnaround_times_p[i]<<" ";
    cout<<endl;


    return 0;
}
