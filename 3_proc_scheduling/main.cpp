#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

/**
 *Process struct - data structure to store input information 
 * 
 * pid, arrival)time, burst_time, priority;
 * 
 **/
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

/**
 * String split helper.
 * */
vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

/**
 * Construct process queue from txt file
 **/
void construct_queue(string filename, vector<Process> &processes) {
    ifstream file(filename);
    string process;
    while(getline(file, process)) {
        vector<string> p_info = split(process, ',');
        struct Process p = Process(p_info[0], stoi(p_info[1]), stoi(p_info[2]), stoi(p_info[3]));
        processes.push_back(p);
    }
}

/**
 * Pairwise sort for 2 vectors
 * 
 **/
void pairsort(vector<string> a, vector<int> b) 
{ 
    int n = a.size();
    pair<string, int> pairt[n]; 
  
    // Storing the respective array 
    // elements in pairs. 
    for (int i = 0; i < n; i++)  
    { 
        pairt[i].first = a[i]; 
        pairt[i].second = b[i]; 
    } 
  
    // Sorting the pair array. 
    sort(pairt, pairt + n); 
      
    // Modifying original arrays 
    for (int i = 0; i < n; i++)  
    { 
        a[i] = pairt[i].first; 
        b[i] = pairt[i].second; 
    } 
} 

/**
 * Average of input vector
 * 
 **/
string average(vector<int> v) {
    float sum = 0;
    for(auto i : v) {
        sum += i;
    }
    sum = sum / (float)v.size();
    return to_string(sum);
}

/**
 * First Come First Serve algorithm implementation
 * 
 * */
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

    /**
     * Compare function to sort input queue
     * 
     **/
    static bool compare(Process p1, Process p2) {
        if(p1.arrival_time != p2.arrival_time)
        return p1.arrival_time < p2.arrival_time;
        else return p1.burst_time < p2.burst_time;
    }

    void setup() {
        sort(modified_processes.begin(), modified_processes.end(), compare);
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

/**
 * Priority algorithm implementation
 * 
 * */
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

        /**
         * Compare function to sort input queue
         * 
         **/
        static bool compare(Process p1, Process p2) {
            if(p1.arrival_time == p2.arrival_time) return p1.priority > p2.priority;
            else return p1.arrival_time < p2.arrival_time;
        }

        void setup() {
            sort(modified_processes.begin(), modified_processes.end(), compare);
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

/**
 * Round Robin algorithm implementation
 * 
 * */
class RoundRobin
{
    private:
        vector<Process> processes;
        vector<Process> modified_processes;

    public:
        int quantum_time;
        RoundRobin(vector<Process> &processes, int quantum_time) {
            copy(processes.begin(), processes.end(), back_inserter(this->processes));
            copy(processes.begin(), processes.end(), back_inserter(this->modified_processes));
            this->quantum_time = quantum_time;
        }

        /**
         * Compare function to sort input queue
         * 
         **/
        static bool compare(Process p1, Process p2) {
            if(p1.arrival_time != p2.arrival_time) return p1.arrival_time < p2.arrival_time;
            else p1.pid < p2.pid;
        }

        void setup() {
            sort(modified_processes.begin(), modified_processes.end(), compare);
        }

        void getCompletionTime(vector<int> &completion_time) {
            this->setup();
            queue<Process> q;
            int t = 0;
            vector<int> compl_time;
            vector<string> process_order;
            int quant_rem = quantum_time;
            bool flag = true;
            while(flag) {
                queue<Process> temp_q;
                for(auto p : modified_processes) {
                    if(p.arrival_time == t) {
                        temp_q.push(p);
                    }
                }
                if(!q.empty()) {
                    Process *current_execution = &q.front();
                    if(current_execution->burst_time >= quantum_time) {
                        current_execution->burst_time -= 1;
                        quant_rem -= 1;
                        if(quant_rem == 0) {
                            q.pop();
                            q.push(*current_execution);
                            quant_rem = quantum_time;
                        }
                    } else {
                        current_execution->burst_time -= 1;
                        if(current_execution->burst_time == 0) {
                            quant_rem = quantum_time;
                            compl_time.push_back(t);
                            process_order.push_back(current_execution->pid);
                            q.pop();
                        }
                    }
                }
                while(!temp_q.empty()) {
                    q.push(temp_q.front());
                    temp_q.pop();
                }
                t += 1;
                if(compl_time.size() == modified_processes.size()) flag=false;
            }
            pairsort(process_order, compl_time);
            copy(compl_time.begin(), compl_time.end(), back_inserter(completion_time));
        }

        void getTurnAroundTime(vector<int> &completion_time, vector<int> &turnaround_time) {
            for(int i=0; i<completion_time.size(); i++) {
                turnaround_time.push_back(completion_time[i]-modified_processes[i].arrival_time);
            }
        }

        void getWaitingTime(vector<int> &turnaround_time, vector<int> &waiting_time) {
            for(int i=0; i<turnaround_time.size(); i++) {
                waiting_time.push_back(turnaround_time[i]-modified_processes[i].burst_time);
            }
        }
};

/**
 * Shortest Job First(Non preemtive) algorithm implementation
 * 
 * */
class SJFNP
{
    private:
        vector<Process> processes;
        vector<Process> modified_processes;
    public:
        SJFNP(vector<Process> &processes) {
            copy(processes.begin(), processes.end(), back_inserter(this->processes));
            copy(processes.begin(), processes.end(), back_inserter(this->modified_processes));
        }

        /**
         * Compare function to sort input queue
         * 
         **/
        static bool compare(Process p1, Process p2) {
            if(p1.arrival_time == p2.arrival_time) return p1.burst_time < p2.burst_time;
            else return p1.arrival_time < p2.arrival_time;
        }

        /**
         * Compare function to sort burst time based queue.
         * 
         **/
        static bool compare_burst(Process p1, Process p2) {
            if(p1.burst_time == p2.burst_time) return p1.arrival_time < p2.arrival_time;
            else return p1.burst_time < p2.burst_time;
        }

        void setup() {
            sort(modified_processes.begin(), modified_processes.end(), compare);
        }

        void getCompletionTime(vector<int> &completion_times) {
            this->setup();
            vector<Process> q;
            int t = 0;
            vector<int> compl_times;
            vector<string> process_order;
            bool flag = true;
            while(flag) {
                t += 1;
                for(auto p: modified_processes) {
                    if(p.arrival_time == t) q.push_back(p);
                }
                if(!q.empty()) {
                    sort(q.begin(), q.end(), compare_burst);
                    for(int i=t+1;i<t+q.front().burst_time;i++){
                        for(auto p: modified_processes) {
                            if(p.arrival_time == i) q.push_back(p);
                        }
                    }
                    t += (q.front().burst_time);
                    compl_times.push_back(t);
                    process_order.push_back(q.front().pid);
                    t -= 1;
                    q.erase(q.begin());
                }
                if(compl_times.size() == processes.size()) flag = false;
            }
            pairsort(process_order, compl_times);
            copy(compl_times.begin(), compl_times.end(), back_inserter(completion_times));
        }

        void getTurnAroundTime(vector<int> &completion_time, vector<int> &turnaround_time) {
            for(int i=0; i<completion_time.size(); i++) {
                turnaround_time.push_back(completion_time[i]-modified_processes[i].arrival_time);
            }
        }

        void getWaitingTime(vector<int> &turnaround_time, vector<int> &waiting_time) {
            for(int i=0; i<turnaround_time.size(); i++) {
                waiting_time.push_back(turnaround_time[i]-modified_processes[i].burst_time);
            }
        }
};

/**
 * Shortest Job First(Preemtive) algorithm implementation
 * 
 * */
class SJFP
{
    private:
        vector<Process> processes;
        vector<Process> modified_processes;
    public:
        SJFP(vector<Process> &processes) {
            copy(processes.begin(), processes.end(), back_inserter(this->processes));
            copy(processes.begin(), processes.end(), back_inserter(this->modified_processes));
        }

        /**
         * Compare function to sort input queue
         * 
         **/
        static bool compare(Process p1, Process p2) {
            if(p1.arrival_time == p2.arrival_time) return p1.burst_time < p2.burst_time;
            else return p1.arrival_time < p2.arrival_time;
        }

        static bool compare_burst(Process p1, Process p2) {
            if(p1.burst_time == p2.burst_time) return p1.arrival_time < p2.arrival_time;
            else return p1.burst_time < p2.burst_time;
        }

        void setup() {
            sort(modified_processes.begin(), modified_processes.end(), compare);
        }

        void getCompletionTime(vector<int> &completion_times) {
            this->setup();
            vector<Process> q;
            int t = 0;
            vector<int> compl_times;
            vector<string> process_order;
            bool flag = true;
            while(flag) {
                for(auto p: modified_processes) {
                    if(p.arrival_time == t) q.push_back(p);
                }
                if(!q.empty()) {
                    sort(q.begin(), q.end(), compare_burst);
                    Process current_process = q.front();
                    q.front().burst_time -= 1;
                    if(q.front().burst_time == 0) {
                        compl_times.push_back(t+1);
                        process_order.push_back(q.front().pid);
                        q.erase(q.begin());
                    }
                }   
                t += 1;
                if(compl_times.size() == processes.size()) flag = false;
            }
            pairsort(process_order, compl_times);
            copy(compl_times.begin(), compl_times.end(), back_inserter(completion_times));
        }

        void getTurnAroundTime(vector<int> &completion_time, vector<int> &turnaround_time) {
            for(int i=0; i<completion_time.size(); i++) {
                turnaround_time.push_back(completion_time[i]-modified_processes[i].arrival_time);
            }
        }

        void getWaitingTime(vector<int> &turnaround_time, vector<int> &waiting_time) {
            for(int i=0; i<turnaround_time.size(); i++) {
                waiting_time.push_back(turnaround_time[i]-modified_processes[i].burst_time);
            }
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

    Priority p(processes);
    vector<int> waiting_times_p(processes.size(), 0);
    vector<int> turnaround_times_p(processes.size(), 0);
    p.getWaitingTimes(waiting_times_p);
    p.getTurnaroundTimes(waiting_times_p, turnaround_times_p);

    RoundRobin rr(processes, 2);
    vector<int> completion_time_r, waiting_times_r, turnaround_times_r;
    rr.getCompletionTime(completion_time_r);
    rr.getTurnAroundTime(completion_time_r, turnaround_times_r);
    rr.getWaitingTime(turnaround_times_r, waiting_times_r);


    SJFNP snp(processes);
    vector<int> completion_time_np, waiting_times_np, turnaround_times_np;
    snp.getCompletionTime(completion_time_np);
    snp.getTurnAroundTime(completion_time_np, turnaround_times_np);
    snp.getWaitingTime(turnaround_times_np, waiting_times_np);

    SJFP sp(processes);
    vector<int> completion_time_sp, waiting_times_sp, turnaround_times_sp;
    sp.getCompletionTime(completion_time_sp);
    sp.getTurnAroundTime(completion_time_sp, turnaround_times_sp);
    sp.getWaitingTime(turnaround_times_sp, waiting_times_sp);

    ofstream stats;
    stats.open("stats.txt");
    stats<<average(waiting_times).append(",");
    stats<<average(waiting_times_p).append(",");
    stats<<average(waiting_times_r).append(",");
    stats<<average(waiting_times_np).append(",");
    stats<<average(waiting_times_sp);
    stats<<"\n";
    stats<<average(turnaround_times).append(",");
    stats<<average(turnaround_times_p).append(",");
    stats<<average(turnaround_times_r).append(",");
    stats<<average(turnaround_times_np).append(",");
    stats<<average(turnaround_times_sp);
    stats<<"\n";
    stats.close();
    return 0;
}
