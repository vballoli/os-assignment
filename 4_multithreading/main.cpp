#include<thread>
#include<bits/stdc++.h>

using namespace std;

int maximum, minimum;
float average;

void display(vector<int> &nums)
{
    for(vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

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

void avg(vector<int> &nums)
{
    average = accumulate(nums.begin(), nums.end(), 0)/nums.size();
}

void max(vector<int> &nums)
{
    maximum = *max_element(nums.begin(), nums.end());
}

void min(vector<int> &nums)
{
    minimum = *min_element(nums.begin(), nums.end());
}

void display_statistics()
{
    cout << "The average is " << average << endl;
    cout << "The min element is " << minimum << endl;
    cout << "The max element is " << maximum << endl;
}

int main()
{
    vector<int> nums;
    nums = input_nums();
    // display(nums);

    avg(nums);
    min(nums);
    max(nums);
    return 0;
}
