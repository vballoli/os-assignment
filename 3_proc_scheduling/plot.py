import matplotlib.pyplot as plt

with open('stats.txt', 'r') as f:
    data = f.readlines()
    waiting_times = data[0].strip('\n').split(',')
    turnaround_times = data[1].strip('\n').split(',')
    labels = ['FCFS', 'Priority', 'RoundRobin', 'SJF(NP)', 'SJF(P)']
    plt.plot(labels, waiting_times, 'ro', label='Avg Waiting times')
    plt.plot(labels, turnaround_times, 'bo', label='Avg Turnaround times')
    plt.legend()
    plt.savefig('stats.png')