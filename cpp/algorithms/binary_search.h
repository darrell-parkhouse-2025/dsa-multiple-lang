#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

/**
 * Binary Search Algorithm Implementation
 * 
 * Time Complexity: O(log n) - divides search space in half each iteration
 * Space Complexity: 
 * - Iterative: O(1)
 * - Recursive: O(log n) due to recursion stack
 * 
 * Binary search works on sorted arrays by repeatedly dividing the search
 * interval in half and comparing the target with the middle element.
 */

namespace BinarySearch {
    
    /**
     * Iterative Binary Search implementation
     * @param arr Sorted array to search in
     * @param target Value to search for
     * @return Index of target if found, -1 otherwise
     */
    template<typename T>
    int iterativeSearch(const std::vector<T>& arr, const T& target) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;  // Avoid overflow
            
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;  // Target not found
    }
    
    /**
     * Recursive Binary Search implementation
     * @param arr Sorted array to search in
     * @param target Value to search for
     * @param left Left boundary of search range
     * @param right Right boundary of search range
     * @return Index of target if found, -1 otherwise
     */
    template<typename T>
    int recursiveSearch(const std::vector<T>& arr, const T& target, int left, int right) {
        if (left > right) {
            return -1;  // Base case: target not found
        }
        
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            return recursiveSearch(arr, target, mid + 1, right);
        } else {
            return recursiveSearch(arr, target, left, mid - 1);
        }
    }
    
    /**
     * Public interface for recursive search
     * @param arr Sorted array to search in
     * @param target Value to search for
     * @return Index of target if found, -1 otherwise
     */
    template<typename T>
    int recursiveSearch(const std::vector<T>& arr, const T& target) {
        if (arr.empty()) return -1;
        return recursiveSearch(arr, target, 0, arr.size() - 1);
    }
    
    /**
     * Find first occurrence of target (leftmost)
     * Useful when array contains duplicates
     * @param arr Sorted array to search in
     * @param target Value to search for
     * @return Index of first occurrence, -1 if not found
     */
    template<typename T>
    int findFirst(const std::vector<T>& arr, const T& target) {
        int left = 0;
        int right = arr.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                result = mid;
                right = mid - 1;  // Continue searching left half
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    /**
     * Find last occurrence of target (rightmost)
     * Useful when array contains duplicates
     * @param arr Sorted array to search in
     * @param target Value to search for
     * @return Index of last occurrence, -1 if not found
     */
    template<typename T>
    int findLast(const std::vector<T>& arr, const T& target) {
        int left = 0;
        int right = arr.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                result = mid;
                left = mid + 1;  // Continue searching right half
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    /**
     * Count occurrences of target in sorted array
     * @param arr Sorted array to search in
     * @param target Value to count
     * @return Number of occurrences
     */
    template<typename T>
    int countOccurrences(const std::vector<T>& arr, const T& target) {
        int first = findFirst(arr, target);
        if (first == -1) return 0;
        
        int last = findLast(arr, target);
        return last - first + 1;
    }
    
    /**
     * Find insertion point for target to maintain sorted order
     * @param arr Sorted array
     * @param target Value to find insertion point for
     * @return Index where target should be inserted
     */
    template<typename T>
    int findInsertionPoint(const std::vector<T>& arr, const T& target) {
        int left = 0;
        int right = arr.size();
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
    
    /**
     * Search in rotated sorted array
     * @param arr Rotated sorted array
     * @param target Value to search for
     * @return Index of target if found, -1 otherwise
     */
    template<typename T>
    int searchRotated(const std::vector<T>& arr, const T& target) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                return mid;
            }
            
            // Check which half is sorted
            if (arr[left] <= arr[mid]) {
                // Left half is sorted
                if (target >= arr[left] && target < arr[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // Right half is sorted
                if (target > arr[mid] && target <= arr[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
    
    /**
     * Find peak element in array (element greater than its neighbors)
     * @param arr Array to search in
     * @return Index of a peak element
     */
    template<typename T>
    int findPeak(const std::vector<T>& arr) {
        if (arr.empty()) return -1;
        if (arr.size() == 1) return 0;
        
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Check if mid is a peak
            bool leftOk = (mid == 0) || (arr[mid] >= arr[mid - 1]);
            bool rightOk = (mid == static_cast<int>(arr.size()) - 1) || (arr[mid] >= arr[mid + 1]);
            
            if (leftOk && rightOk) {
                return mid;
            } else if (mid > 0 && arr[mid - 1] > arr[mid]) {
                right = mid - 1;  // Peak is in left half
            } else {
                left = mid + 1;   // Peak is in right half
            }
        }
        
        return -1;
    }
    
    /**
     * Binary search with custom comparator
     * @param arr Sorted array
     * @param target Value to search for
     * @param comp Custom comparator function
     * @return Index of target if found, -1 otherwise
     */
    template<typename T, typename Compare>
    int searchWithComparator(const std::vector<T>& arr, const T& target, Compare comp) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (!comp(arr[mid], target) && !comp(target, arr[mid])) {
                // arr[mid] == target according to comparator
                return mid;
            } else if (comp(arr[mid], target)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
    /**
     * Search for target in 2D sorted matrix
     * Matrix is sorted row-wise and column-wise
     * @param matrix 2D sorted matrix
     * @param target Value to search for
     * @return Pair of indices if found, {-1, -1} otherwise
     */
    template<typename T>
    std::pair<int, int> search2D(const std::vector<std::vector<T>>& matrix, const T& target) {
        if (matrix.empty() || matrix[0].empty()) {
            return {-1, -1};
        }
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        int left = 0;
        int right = rows * cols - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int row = mid / cols;
            int col = mid % cols;
            
            if (matrix[row][col] == target) {
                return {row, col};
            } else if (matrix[row][col] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return {-1, -1};
    }
    
    /**
     * Public interface for standard binary search
     * @param arr Sorted array to search in
     * @param target Value to search for
     * @return Index of target if found, -1 otherwise
     */
    template<typename T>
    int search(const std::vector<T>& arr, const T& target) {
        return iterativeSearch(arr, target);
    }
    
    /**
     * Utility function to verify if array is sorted
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
    
    /**
     * Utility function to print search result
     * @param result Index returned by search
     * @param target Value that was searched for
     */
    template<typename T>
    void printResult(int result, const T& target) {
        if (result != -1) {
            std::cout << "Found " << target << " at index " << result << std::endl;
        } else {
            std::cout << "Target " << target << " not found" << std::endl;
        }
    }
}

#endif // BINARY_SEARCH_H
