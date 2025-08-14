#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

/**
 * Quick Sort Algorithm Implementation
 * 
 * Time Complexity:
 * - Best Case: O(n log n) - when pivot divides array into equal halves
 * - Average Case: O(n log n) - expected performance
 * - Worst Case: O(n²) - when pivot is always smallest/largest element
 * 
 * Space Complexity: O(log n) - due to recursion stack
 * 
 * Quick Sort is a divide-and-conquer algorithm that works by selecting a 'pivot'
 * element and partitioning the array around it.
 */

namespace QuickSort {
    
    /**
     * Partition function using Lomuto partition scheme
     * Places pivot at correct position and returns its index
     * @param arr Array to partition
     * @param low Starting index
     * @param high Ending index
     * @return Index of pivot after partitioning
     */
    template<typename T>
    int partition(std::vector<T>& arr, int low, int high) {
        T pivot = arr[high];  // Choose last element as pivot
        int i = low - 1;      // Index of smaller element
        
        for (int j = low; j < high; j++) {
            // If current element is smaller than or equal to pivot
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    /**
     * Hoare partition scheme (alternative partitioning method)
     * More efficient in terms of swaps
     * @param arr Array to partition
     * @param low Starting index
     * @param high Ending index
     * @return Index for next partitioning
     */
    template<typename T>
    int hoarePartition(std::vector<T>& arr, int low, int high) {
        T pivot = arr[low];  // Choose first element as pivot
        int i = low - 1;
        int j = high + 1;
        
        while (true) {
            do {
                i++;
            } while (arr[i] < pivot);
            
            do {
                j--;
            } while (arr[j] > pivot);
            
            if (i >= j) {
                return j;
            }
            
            std::swap(arr[i], arr[j]);
        }
    }
    
    /**
     * Randomized partition to avoid worst-case performance
     * @param arr Array to partition
     * @param low Starting index
     * @param high Ending index
     * @return Index of pivot after partitioning
     */
    template<typename T>
    int randomizedPartition(std::vector<T>& arr, int low, int high) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(low, high);
        
        int randomIndex = dis(gen);
        std::swap(arr[randomIndex], arr[high]);
        
        return partition(arr, low, high);
    }
    
    /**
     * Recursive Quick Sort implementation
     * @param arr Array to sort
     * @param low Starting index
     * @param high Ending index
     */
    template<typename T>
    void quickSortRecursive(std::vector<T>& arr, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            
            // Recursively sort elements before and after partition
            quickSortRecursive(arr, low, pivotIndex - 1);
            quickSortRecursive(arr, pivotIndex + 1, high);
        }
    }
    
    /**
     * Randomized Quick Sort to avoid worst-case performance
     * @param arr Array to sort
     * @param low Starting index
     * @param high Ending index
     */
    template<typename T>
    void randomizedQuickSort(std::vector<T>& arr, int low, int high) {
        if (low < high) {
            int pivotIndex = randomizedPartition(arr, low, high);
            
            randomizedQuickSort(arr, low, pivotIndex - 1);
            randomizedQuickSort(arr, pivotIndex + 1, high);
        }
    }
    
    /**
     * Iterative Quick Sort implementation using explicit stack
     * Avoids recursion overhead and potential stack overflow
     * @param arr Array to sort
     */
    template<typename T>
    void quickSortIterative(std::vector<T>& arr) {
        if (arr.size() <= 1) return;
        
        std::vector<std::pair<int, int>> stack;
        stack.push_back({0, static_cast<int>(arr.size()) - 1});
        
        while (!stack.empty()) {
            auto [low, high] = stack.back();
            stack.pop_back();
            
            if (low < high) {
                int pivotIndex = partition(arr, low, high);
                
                // Push left and right subarrays to stack
                stack.push_back({low, pivotIndex - 1});
                stack.push_back({pivotIndex + 1, high});
            }
        }
    }
    
    /**
     * Three-way partitioning for handling duplicate elements efficiently
     * Useful when array has many duplicate elements
     * @param arr Array to sort
     * @param low Starting index
     * @param high Ending index
     * @param lt Reference to store index of less-than partition
     * @param gt Reference to store index of greater-than partition
     */
    template<typename T>
    void threeWayPartition(std::vector<T>& arr, int low, int high, int& lt, int& gt) {
        T pivot = arr[low];
        int i = low;
        lt = low;
        gt = high;
        
        while (i <= gt) {
            if (arr[i] < pivot) {
                std::swap(arr[lt], arr[i]);
                lt++;
                i++;
            } else if (arr[i] > pivot) {
                std::swap(arr[i], arr[gt]);
                gt--;
            } else {
                i++;
            }
        }
    }
    
    /**
     * Three-way Quick Sort for arrays with duplicates
     * @param arr Array to sort
     * @param low Starting index
     * @param high Ending index
     */
    template<typename T>
    void threeWayQuickSort(std::vector<T>& arr, int low, int high) {
        if (low >= high) return;
        
        int lt, gt;
        threeWayPartition(arr, low, high, lt, gt);
        
        threeWayQuickSort(arr, low, lt - 1);
        threeWayQuickSort(arr, gt + 1, high);
    }
    
    /**
     * Public interface for standard Quick Sort
     * @param arr Array to sort
     */
    template<typename T>
    void sort(std::vector<T>& arr) {
        if (!arr.empty()) {
            quickSortRecursive(arr, 0, arr.size() - 1);
        }
    }
    
    /**
     * Public interface for randomized Quick Sort
     * @param arr Array to sort
     */
    template<typename T>
    void randomizedSort(std::vector<T>& arr) {
        if (!arr.empty()) {
            randomizedQuickSort(arr, 0, arr.size() - 1);
        }
    }
    
    /**
     * Public interface for iterative Quick Sort
     * @param arr Array to sort
     */
    template<typename T>
    void iterativeSort(std::vector<T>& arr) {
        quickSortIterative(arr);
    }
    
    /**
     * Public interface for three-way Quick Sort
     * @param arr Array to sort
     */
    template<typename T>
    void threeWaySort(std::vector<T>& arr) {
        if (!arr.empty()) {
            threeWayQuickSort(arr, 0, arr.size() - 1);
        }
    }
    
    /**
     * Utility function to print array
     * @param arr Array to print
     * @param title Title for the output
     */
    template<typename T>
    void printArray(const std::vector<T>& arr, const std::string& title = "Array") {
        std::cout << title << ": ";
        for (const auto& element : arr) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    
    /**
     * Utility function to check if array is sorted
     * @param arr Array to check
     * @return true if sorted, false otherwise
     */
    template<typename T>
    bool isSorted(const std::vector<T>& arr) {
        for (size_t i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i-1]) {
                return false;
            }
        }
        return true;
    }
}

#endif // QUICK_SORT_H
