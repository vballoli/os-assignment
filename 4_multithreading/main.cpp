#include<algorithm>
#include<thread>
#include<iostream>
#include<string.h>
#include<vector>
#include<cmath>
#include<numeric>

using namespace std;

// Declaring variables to be set by threads gloablly
int maximum, minimum, c_nums;
float average, sd, median;
vector<int> nums;

// Function used to input array of numbers from console
vector<int> input_nums()
{
    vector<int> nums;
    int size, t;
    cout << "Enter the size of array of numbers:" << endl;
    cin >> size;
    cout << "Enter the numbers:" << endl;
    for (int i=0; i<size; i++)
    {
        cin >> t;
        nums.push_back(t);
    }

    return nums;
}

// Function to compute average of all entered numbers
void avg()
{
    average = accumulate(nums.begin(), nums.end(), 0)/nums.size();
}

// Function to compute max of all entered numbers
void max_fn()
{
    maximum = *max_element(nums.begin(), nums.end());
}

// Function to compute min of all entered numbers
void min_fn()
{
    minimum = *min_element(nums.begin(), nums.end());
}

void count_nums()
{
    c_nums = nums.size();
}

void standard_deviation()
{
    float mean = accumulate(nums.begin(), nums.end(), 0) / nums.size();
    float variance=0.0;
    for (vector<int>::iterator i=nums.begin(); i != nums.end(); ++i)
    {
        variance += pow(*i - mean, 2);
    }
    sd = sqrt(variance);
}

void median_fn()
{
    sort(nums.begin(), nums.end());
    if (nums.size()%2 != 0)
        median = nums[nums.size()/2];
    else
        median = (nums[nums.size()/2] + nums[(nums.size()-1)/2])/2;
}

// Function to display all computed statistics which are stored globally
void display_statistics()
{
    cout << "The average is " << average << endl;
    cout << "The min element is " << minimum << endl;
    cout << "The max element is " << maximum << endl;
    cout << "The median is  " << median << endl;
    cout << "The standard deviation is " << sd << endl;
    cout << "The total number of elements are " << c_nums << endl;
}

int main(int argc,  char** argv)
{
    nums = input_nums();

    // Assigning different threads to all computations
    thread t1(avg);
    thread t2(min_fn);
    thread t3(max_fn);
    thread t4(median_fn);
    thread t5(standard_deviation);
    thread t6(count_nums);

    // Display PIDs for the worker threads
    if (argc > 1 && strcmp(argv[1], "print_pids") == 0)
    {
        cout << "PID for thread 1 - average: " << t1.get_id() << endl;
        cout << "PID for thread 2 - min: " << t2.get_id() << endl;
        cout << "PID for thread 3 - max: " << t3.get_id() << endl;
        cout << "PID for thread 4 - median: " << t4.get_id() << endl;
        cout << "PID for thread 5 - standard deviation: " << t5.get_id() << endl;
        cout << "PID for thread 6 - count elements: " << t6.get_id() << endl;
    }

    // Waiting for all threads to complete exectution
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    // Displaying computed statistics after execution of all worker threads
    display_statistics();

    return 0;
}
