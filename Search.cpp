// AUTHOR: William Kavanagh. Abertay University. CMP201.2022
// Minimal Framework for AX1.3, searching

// Solution by Sam Collier - 2100259

#include "Search.h"
#include <vector>
#include <stdlib.h>		// for RNG
#include <time.h>		// for RNG
#include <iostream>
#include <chrono>		// for timing
#include <map>
#include <cmath>


// Return index position of key in arr or -1 if not in collection.
// Search using a naive scan.
int LinearScan(std::vector<int> arr, int key)
{
	// TODO: Assessed [1]
	for(int i=0; i<arr.size(); i++)
	{
		if(arr[i] == key)
		{
			return i;
		}
	}
	return -1;
}

// Return index position of key in arr or -1 if not in collection.
// Search using binary reduction
int BinarySearch(std::vector<int> arr, int key)
{
	// TODO: Assessed [1]

	int start = 0;
	int end = arr.size()-1;

	while(start <= end)
	{
		int mid = std::floor((start+end)/2.f);

		if(arr[mid] == key)
		{
			return mid;
		}

		if(key < arr[mid])
		{
			end = mid-1;
		}
		else
		{
			start = mid+1;
		}
	}

	return -1;
}

// Return index position of key in arr or -1 if not in collection.
// Search using interpolation guestimates.
int InterpolationSearch(std::vector<int> arr, int key)
{
	// TODO: Assessed [1]

	int start = 0;
	int end = arr.size()-1;

	while(start <= end && key >= arr[start] && key <= arr[end])
	{
		int dist = key - arr[start];
		int valRange = arr[end]-arr[start];
		int fraction = std::floor((float)dist/valRange);
		int indexRange = end-start;
		int estimate = start + fraction * indexRange;

		if(arr[estimate] == key)
		{
			return estimate;
		}

		if(key < arr[estimate])
		{
			end = estimate-1;
		}
		else
		{
			start = estimate+1;
		}
	}

	return -1;
}

/*
Generate a vector of length <size> where each element is
1-5 larger than the previous element.
*/
std::vector<int> SortedVectorGenerator(int size)
{
	// TODO: Unassessed.
		// Check with implementation from partial framework before submitting.

	srand(time(0));
	std::vector<int> v;

	if(size > 0)
	{
		v.push_back(rand() % 5 + 1);
	}

	for(int i=1;i<size;i++)
	{
		v.push_back(v[i-1] + rand() % 5 + 1);
	}

	return v;
}

std::vector<int> EvenlyDistributedVectorGenerator(int size)
{
	// TODO: Unassessed.
		// Check with implementation from partial framework before submitting.

	srand(time(0));
	std::vector<int> v;

	int dist = rand() % 5 + 1;

	if(size > 0)
	{
		v.push_back(dist);
	}

	for(int i=1;i<size;i++)
	{
		v.push_back(v[i-1] + dist);
	}

	return v;
}

// Runs the three searches on the three vectors with the three targets supplied as parameters.
// i.e. LS(v0, t0), BS(v0, t0), IS(v0, t0), LS(v1, t1), ... etc.
// Returns a map of search name to vector of doubles with timing results in nanoseconds.
// Example map output:
//		"binary search":{13400, 6400, 238100}
//		"interpolation search":{2500, 303800, 237100}
//		"linear scan":{2200, 59700, 1.4251e+06}
std::map<std::string, std::vector<double>> 
runTests(std::vector<int> v0, std::vector<int> v1, std::vector<int> v2,
int t0, int t1, int t2)
{
	// TODO: Assessed [2]

	//KEYS
	const std::string LINEAR_SCAN = "linear scan";
	const std::string BINARY_SEARCH = "binary search";
	const std::string INTERPOLATION_SEARCH = "interpolation search";

	std::map<std::string,std::vector<double>> results;

	// linear scan
	auto start = std::chrono::high_resolution_clock::now();
	LinearScan(v0,t0);
	auto end = std::chrono::high_resolution_clock::now();
	results[LINEAR_SCAN].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());
	
	start = std::chrono::high_resolution_clock::now();
	LinearScan(v1,t1);
	end = std::chrono::high_resolution_clock::now();
	results[LINEAR_SCAN].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());

	start = std::chrono::high_resolution_clock::now();
	LinearScan(v2,t2);
	end = std::chrono::high_resolution_clock::now();
	results[LINEAR_SCAN].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());


	// binary search
	start = std::chrono::high_resolution_clock::now();
	BinarySearch(v0,t0);
	end = std::chrono::high_resolution_clock::now();
	results[BINARY_SEARCH].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());

	start = std::chrono::high_resolution_clock::now();
	BinarySearch(v1,t1);
	end = std::chrono::high_resolution_clock::now();
	results[BINARY_SEARCH].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());

	start = std::chrono::high_resolution_clock::now();
	BinarySearch(v2,t2);
	end = std::chrono::high_resolution_clock::now();
	results[BINARY_SEARCH].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());


	// interpolation search
	start = std::chrono::high_resolution_clock::now();
	InterpolationSearch(v0,t0);
	end = std::chrono::high_resolution_clock::now();
	results[INTERPOLATION_SEARCH].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());

	start = std::chrono::high_resolution_clock::now();
	InterpolationSearch(v1,t1);
	end = std::chrono::high_resolution_clock::now();
	results[INTERPOLATION_SEARCH].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());

	start = std::chrono::high_resolution_clock::now();
	InterpolationSearch(v2,t2);
	end = std::chrono::high_resolution_clock::now();
	results[INTERPOLATION_SEARCH].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());

	return results;
	
}

// Provided for testing purposes. Remove or delete entirely (including signature) or [-1]
int main()
{
	// Test individual algs.
	std::vector<int> a;
	for (int i = 1; i < 101; i++)
	{
		a.push_back(i);
	}
	std::cout << "Single algorithm executions. Expecting indexed position or -1 if not found.\n\n";
	std::cout << "Linear scan for 7 on 1-100 returns: " << LinearScan(a, 7) << std::endl;
	std::cout << "Binary search for 7 on 1-100 returns: " << BinarySearch(a, 7) << std::endl;
	std::cout << "Interpolation search for 7 on 1-100 returns: " << InterpolationSearch(a, 7) << std::endl << std::endl;

	std::cout << "Linear scan for 101 on 1-100 returns: " << LinearScan(a, 101) << std::endl;
	std::cout << "Binary search for 101 on 1-100 returns: " << BinarySearch(a, 101) << std::endl;
	std::cout << "Interpolation search for 101 on 1-100 returns: " << InterpolationSearch(a, 101) << std::endl;


	// Prepare vectors and targets for test.
	std::vector<int> v0 = SortedVectorGenerator(1000);
	std::vector<int> v1 = SortedVectorGenerator(10000);
	std::vector<int> v2 = EvenlyDistributedVectorGenerator(100000);
	int t0 = v0[10];			
	int t1 = v1[4999];
	int t2 = 1000000*5 + 1;


	// Run tests.
	std::map < std::string, std::vector<double>> res = runTests(v0, v1, v2, t0, t1, t2);

	std::cout << "\n~~~~~~~~~~~~~~~~\nTest() execution. We are expecting output of the form:\n";
	std::cout << "\nbinary search : _value, _value, _value\nInterpolation search : ...\nlinear scan : ...\n\n";

	// Display results.
	for (std::pair<std::string, std::vector<double>> p : res)
	{
		std::cout << p.first << " results = ";
		std::cout << p.second[0] << ", " << p.second[1] << ", " << p.second[2] << std::endl;
	}
}

