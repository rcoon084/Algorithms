#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

// Insertion Sort
void insertionSort(std::vector<int> &arr)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

// Generate a random array of integers between min and max
vector<int> generateRandomArray(size_t n, int min = 1, int max = 5000)
{
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    for (auto &val : arr)
    {
        val = dis(gen);
    }
    return arr;
}

// Function to calculate the median
double calculateMedian(vector<double> &times)
{
    sort(times.begin(), times.end());
    size_t size = times.size();
    if (size % 2 == 0)
    {
        return (times[size / 2 - 1] + times[size / 2]) / 2.0;
    }
    else
    {
        return times[size / 2];
    }
}

int main()
{
    double accumulatedTime = 0.0;
    size_t n = 1; // Initial size of the array
    bool timeExceeded = false;
    ofstream output("insertion_sort_results.csv");

    // Write header for CSV
    output << "n,median_time_ms\n";

    while (!timeExceeded)
    {
        vector<double> times;

        for (int exp = 0; exp < 100; ++exp)
        {
            auto arr = generateRandomArray(n);

            auto start = chrono::high_resolution_clock::now();
            insertionSort(arr);
            auto end = chrono::high_resolution_clock::now();

            times.push_back(chrono::duration<double, milli>(end - start).count());
        }

        // Calculate the median time for this n
        double medianTime = calculateMedian(times);
        if (medianTime != 0){
            output << n << "," << medianTime << "\n";
        }else{
            output << n << "," << medianTime + 0.000000001 << "\n";
        }

        cout << "n = " << n << ", Median Time: " << medianTime << " ms\n";

        // Total time of excecution
        double totalTime = 0.0;
        for (const auto &time : times)
        {
            totalTime += time;
        }

        accumulatedTime += totalTime;

        cout << "Accumulated Time: " << accumulatedTime / 60000.0 << " min\n";


        // Stop if the total experiment time exceeds 5 minutes
        if (accumulatedTime > 5 * 60 * 1000)
        {
            timeExceeded = true;
        }
        else
        {
            ++n;
        }
    }

    output.close();
    cout << "Results written to insertion_sort_results.csv" << endl;
    return 0;
}
