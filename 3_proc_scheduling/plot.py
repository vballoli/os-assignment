import matplotlib.pyplot as plt

with open('stats.txt', 'r') as f:
    data = f.readlines()
    waiting_times = data[0].strip('\n').split(',')
    turnaround_times = data[1].strip('\n').split(',')
    print(waiting_times)
    labels = ['FCFS', 'Priority', 'RoundRobin', 'SJF(NP)', 'SJF(P)']
    x_axis = [0, 1, 2, 3, 4]
    x, y = zip(*sorted(zip(waiting_times, x_axis)))
    plt.plot(y, x, 'ro', label='Avg Waiting times')
    x, y = zip(*sorted(zip(turnaround_times, x_axis)))
    plt.plot(y, x, 'bo', label='Avg turnaround times')
    plt.xticks(x_axis, labels)
    plt.legend
    plt.savefig('stats.png')