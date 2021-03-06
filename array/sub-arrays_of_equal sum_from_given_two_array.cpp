/*
Problem Statement-Given two arrays A[] and B[] of equal sizes i.e. N containing integers from 1 to N. 
The task is to find sub-arrays from the given arrays such that they have equal sum. Print the indices of such sub-arrays. 
If no such sub-arrays are possible then print -1.
link:https://www.geeksforgeeks.org/find-sub-arrays-from-given-two-arrays-such-that-they-have-equal-sum/?ref=rp
*/
// C++ implementation of the approach
#include <bits/stdc++.h>
using namespace std;

// Function to print the valid indices in the array
void printAns(int x, int y, int num)
{
	cout << "Indices in array " << num << " : ";
	for (int i = x; i < y; ++i) {
		cout << i << ", ";
	}
	cout << y << "\n";
}

// Function to find sub-arrays from two
// different arrays with equal sum
void findSubarray(int N, int a[], int b[], bool swap)
{

	// Map to store the indices in A and B
	// which produce the given difference
	std::map<int, pair<int, int> > index;
	int difference;
	index[0] = make_pair(-1, -1);
	int j = 0;
	for (int i = 0; i < N; ++i) {

		// Find the smallest j such that b[j] >= a[i]
		while (b[j] < a[i]) {
			j++;
		}
		difference = b[j] - a[i];

		// Difference encountered for the second time
		if (index.find(difference) != index.end()) {

			// b[j] - a[i] = b[idx.second] - a[idx.first]
			// b[j] - b[idx.second] = a[i] = a[idx.first]
			// So sub-arrays are a[idx.first+1...i] and b[idx.second+1...j]
			if (swap) {
				pair<int, int> idx = index[b[j] - a[i]];

				printAns(idx.second + 1, j, 1);
				printAns(idx.first + 1, i, 2);
			}
			else {
				pair<int, int> idx = index[b[j] - a[i]];
				printAns(idx.first + 1, i, 1);
				printAns(idx.second + 1, j, 2);
			}
			return;
		}

		// Store the indices for difference in the map
		index[difference] = make_pair(i, j);
	}

	cout << "-1";
}

// Utility function to calculate the
// cumulative sum of the array
void cumulativeSum(int arr[], int n)
{
	for (int i = 1; i < n; ++i)
		arr[i] += arr[i - 1];
}

// Driver code
int main()
{
	int a[] = { 1, 2, 3, 4, 5 };
	int b[] = { 6, 2, 1, 5, 4 };
	int N = sizeof(a) / sizeof(a[0]);

	// Function to update the arrays
	// with their cumulative sum
	cumulativeSum(a, N);
	cumulativeSum(b, N);

	if (b[N - 1] > a[N - 1]) {
		findSubarray(N, a, b, false);
	}
	else {

		// Swap is true as a and b are swapped during
		// function call
		findSubarray(N, b, a, true);
	}

	return 0;
}
