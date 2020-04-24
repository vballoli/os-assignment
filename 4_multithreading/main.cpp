#include<thread>
#include<bits/stdc++.h>

using namespace std;

void display(vector<int> nums)
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

void avg(vector<int> nums)
{
    float avg;
    avg = accumulate(nums.begin(), nums.end(), 0)/nums.size();
    cout << "The average is " << avg << endl;
}

void max(vector<int> nums)
{
    int max = *max_element(nums.begin(), nums.end());
    cout << "The max element is " << max << endl;
}

void min(vector<int> nums)
{
    int min = *min_element(nums.begin(), nums.end());
    cout << "The min element is " << min << endl;
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
