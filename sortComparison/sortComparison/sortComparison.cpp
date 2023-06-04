#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
using namespace std::chrono;

//Printing the vector.
void printArray(std::vector<int>& numbers)
{
    for (int i = 0; i < numbers.size(); ++i)
        std::cout << numbers[i] << std::endl;
}


//Insertion Sort 
void insertionSort(std::vector<int>& numbers)
{
    std::cout << "Insertion Sort" << std::endl;
    int j;
    int temp;

    for (int i = 0; i < numbers.size(); ++i)
    {
        j = i;
        while (j > 0 && numbers[j] < numbers[j - 1])
        {
            temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            j--;
        }
    }
}



//Bucket sort
void BucketSort(std::vector<int>& numbers, int size) {
    if (size == 0) {
        return;
    }

    // Find the maximum and minimum values in the input array
    int max_val = numbers[0];
    int min_val = numbers[0];
    for (int i = 1; i < numbers.size(); ++i) {
        if (numbers[i] > max_val) {
            max_val = numbers[i];
        }
        if (numbers[i] < min_val) {
            min_val = numbers[i];
        }
    }

    // Calculate the range and the width of each bucket
    int range = max_val - min_val + 1;
    int bucket_width = (range + size - 1) / size;

    // Initialize the buckets
    std::vector<std::vector<int>> buckets(size);

    // Distribute the numbers into the buckets
    for (int i = 0; i < numbers.size(); ++i) {
        int bucket_index = (numbers[i] - min_val) / bucket_width;
        buckets[bucket_index].push_back(numbers[i]);
    }

    // Sort each bucket
    for (int i = 0; i < size; ++i) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    // Concatenate the buckets
    int index = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < buckets[i].size(); ++j) {
            numbers[index++] = buckets[i][j];
        }
    }
}




// Sorting based on the digits
void Sort(std::vector<int>& numbers, int exp)
{
    int n = numbers.size();
    std::vector<int> output(n); // output array
    std::vector<int> count(10, 0); 

    for (int i = 0; i < n; i++)
    {
        count[(numbers[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(numbers[i] / exp) % 10] - 1] = numbers[i];
        count[(numbers[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
    {
        numbers[i] = output[i];
    }
}

// radix sort
void RadixSort(std::vector<int>& numbers)
{
    int max = numbers[0];
    for (int i = 1; i < numbers.size(); i++)
    {
        if (numbers[i] > max)
        {
            max = numbers[i];
        }
    }

    // Sorting for each digits
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        Sort(numbers, exp);
    }
}
int main()
{
    std::vector<int> v = {};
    for (int i = 0; i < 100; i++) {
        v.push_back((rand() % 1000) + 1);

    }
    std::cout << "Before the Sort :" << std::endl;
    //printArray(v);
    auto start = steady_clock::now();

    //insertionSort(v);
    //BucketSort(v, 10);
    RadixSort(v);

    auto duration = steady_clock::now() - start;
    std::cout << "Duration " << duration_cast<milliseconds>(duration).count() << std::endl;
    std::cout << "After the Sort :" << std::endl;
    //printArray(v);
    return (0);
}