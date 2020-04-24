#include<thread>
#include<bits/stdc++.h>

using namespace std;

// Declaring variables to be set by threads gloablly
int maximum, minimum;
float average;
vector<int> nums;

// Function used to print vector contents, used for debugging
void display(vector<int> &nums)
{
    for(vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

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

// Function to display all computed statistics which are stored globally
void display_statistics()
{
    cout << "The average is " << average << endl;
    cout << "The min element is " << minimum << endl;
    cout << "The max element is " << maximum << endl;
}

int main()
{
    nums = input_nums();
    // cout << "The numbers given as input are:" <<endl;
    // display(nums);

    // Assigning different threads to all computations
    thread t1(avg);
    thread t2(min_fn);
    thread t3(max_fn);

    // Display PIDs for the worker threads
    cout << "PID for thread 1 - average computation: " << t1.get_id() << endl;
    cout << "PID for thread 2 - min computation: " << t2.get_id() << endl;
    cout << "PID for thread 3 - max computation: " << t3.get_id() << endl;

    // Waiting for all threads to complete exectution
    t1.join();
    t2.join();
    t3.join();

    // Displaying computed statistics after execution of all worker threads
    display_statistics();

    return 0;
}
