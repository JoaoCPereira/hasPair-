// HasPairSum.h

#ifndef HASPAIRSUM_H
#define HASPAIRSUM_H

#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include "QuickSortMultiThreading.h"

using namespace std;

bool hasPairSum(vector<int> A, int x);

void checkRange(const vector<int>& A, int x, atomic<bool>& found, mutex& coutMutex, int start, int end);
bool hasPairSumThreads(const vector<int>& A, int x, int t);

bool hasPairSumSorted(vector<int>& A, int X);

bool binarySearch(const vector<int>& A, int start, int end, int target);
bool hasPairSumSortedBinarySearch(vector<int>& A, int X);

void checkRangeBinarySearch(const vector<int>& A, int x, atomic<bool>& found, mutex& coutMutex, int start, int end);
bool hasPairSumSortedBinarySearchThreads(vector<int>& A, int X, int t);

#endif // HASPAIRSUM_H