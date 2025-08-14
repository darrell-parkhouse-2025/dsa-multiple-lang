#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

#include <stdexcept>
#include <iostream>

/**
 * Array-based Queue Implementation
 * 
 * Time Complexity:
 * - Enqueue: O(1)
 * - Dequeue: O(1)
 * - Front: O(1)
 * - Size: O(1)
 * - IsEmpty: O(1)
 * 
 * Space Complexity: O(n) where n is the capacity
 */
template <typename T>
class QueueArray {
private:
    T* data;           // Array to store queue elements
    int capacity;      // Maximum capacity of the queue
    int front_idx;     // Index of the front element
    int rear_idx;      // Index of the rear element
    int size;          // Current number of elements

public:
    /**
     * Constructor - Initialize queue with given capacity
     * @param cap Maximum capacity of the queue (default: 100)
     */
    explicit QueueArray(int cap = 100);
    
    /**
     * Destructor - Clean up allocated memory
     */
    ~QueueArray();
    
    /**
     * Copy constructor
     */
    QueueArray(const QueueArray& other);
    
    /**
     * Assignment operator
     */
    QueueArray& operator=(const QueueArray& other);
    
    /**
     * Add element to the rear of the queue
     * @param item Element to be added
     * @throws std::overflow_error if queue is full
     */
    void enqueue(const T& item);
    
    /**
     * Remove and return element from the front of the queue
     * @return Front element
     * @throws std::underflow_error if queue is empty
     */
    T dequeue();
    
    /**
     * Get front element without removing it
     * @return Reference to front element
     * @throws std::underflow_error if queue is empty
     */
    const T& front() const;
    
    /**
     * Get rear element without removing it
     * @return Reference to rear element
     * @throws std::underflow_error if queue is empty
     */
    const T& rear() const;
    
    /**
     * Check if queue is empty
     * @return true if empty, false otherwise
     */
    bool isEmpty() const;
    
    /**
     * Check if queue is full
     * @return true if full, false otherwise
     */
    bool isFull() const;
    
    /**
     * Get current size of queue
     * @return Number of elements in queue
     */
    int getSize() const;
    
    /**
     * Get capacity of queue
     * @return Maximum capacity
     */
    int getCapacity() const;
    
    /**
     * Clear all elements from queue
     */
    void clear();
    
    /**
     * Display queue contents (for debugging)
     */
    void display() const;
};

// Implementation

template <typename T>
QueueArray<T>::QueueArray(int cap) : capacity(cap), front_idx(0), rear_idx(-1), size(0) {
    if (cap <= 0) {
        throw std::invalid_argument("Capacity must be positive");
    }
    data = new T[capacity];
}

template <typename T>
QueueArray<T>::~QueueArray() {
    delete[] data;
}

template <typename T>
QueueArray<T>::QueueArray(const QueueArray& other) 
    : capacity(other.capacity), front_idx(other.front_idx), 
      rear_idx(other.rear_idx), size(other.size) {
    data = new T[capacity];
    for (int i = 0; i < capacity; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
QueueArray<T>& QueueArray<T>::operator=(const QueueArray& other) {
    if (this != &other) {
        delete[] data;
        
        capacity = other.capacity;
        front_idx = other.front_idx;
        rear_idx = other.rear_idx;
        size = other.size;
        
        data = new T[capacity];
        for (int i = 0; i < capacity; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
void QueueArray<T>::enqueue(const T& item) {
    if (isFull()) {
        throw std::overflow_error("Queue is full");
    }
    
    rear_idx = (rear_idx + 1) % capacity;  // Circular array
    data[rear_idx] = item;
    size++;
}

template <typename T>
T QueueArray<T>::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    
    T item = data[front_idx];
    front_idx = (front_idx + 1) % capacity;  // Circular array
    size--;
    return item;
}

template <typename T>
const T& QueueArray<T>::front() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    return data[front_idx];
}

template <typename T>
const T& QueueArray<T>::rear() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    return data[rear_idx];
}

template <typename T>
bool QueueArray<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
bool QueueArray<T>::isFull() const {
    return size == capacity;
}

template <typename T>
int QueueArray<T>::getSize() const {
    return size;
}

template <typename T>
int QueueArray<T>::getCapacity() const {
    return capacity;
}

template <typename T>
void QueueArray<T>::clear() {
    front_idx = 0;
    rear_idx = -1;
    size = 0;
}

template <typename T>
void QueueArray<T>::display() const {
    if (isEmpty()) {
        std::cout << "Queue is empty" << std::endl;
        return;
    }
    
    std::cout << "Queue: ";
    for (int i = 0; i < size; ++i) {
        int idx = (front_idx + i) % capacity;
        std::cout << data[idx];
        if (i < size - 1) std::cout << " <- ";
    }
    std::cout << " (front: " << data[front_idx] << ", rear: " << data[rear_idx] << ")" << std::endl;
}

#endif // QUEUE_ARRAY_H
