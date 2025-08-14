#ifndef QUEUE_LINKED_H
#define QUEUE_LINKED_H

#include <stdexcept>
#include <iostream>

/**
 * Linked List-based Queue Implementation
 * 
 * Time Complexity:
 * - Enqueue: O(1)
 * - Dequeue: O(1)
 * - Front: O(1)
 * - Size: O(1)
 * - IsEmpty: O(1)
 * 
 * Space Complexity: O(n) where n is the number of elements
 */
template <typename T>
class QueueLinked {
private:
    /**
     * Node structure for the linked list
     */
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* front_ptr;    // Pointer to front node
    Node* rear_ptr;     // Pointer to rear node
    int size;           // Current number of elements

public:
    /**
     * Constructor - Initialize empty queue
     */
    QueueLinked();
    
    /**
     * Destructor - Clean up all nodes
     */
    ~QueueLinked();
    
    /**
     * Copy constructor
     */
    QueueLinked(const QueueLinked& other);
    
    /**
     * Assignment operator
     */
    QueueLinked& operator=(const QueueLinked& other);
    
    /**
     * Add element to the rear of the queue
     * @param item Element to be added
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
     * Get current size of queue
     * @return Number of elements in queue
     */
    int getSize() const;
    
    /**
     * Clear all elements from queue
     */
    void clear();
    
    /**
     * Display queue contents (for debugging)
     */
    void display() const;

private:
    /**
     * Helper function to copy from another queue
     */
    void copyFrom(const QueueLinked& other);
};

// Implementation

template <typename T>
QueueLinked<T>::QueueLinked() : front_ptr(nullptr), rear_ptr(nullptr), size(0) {}

template <typename T>
QueueLinked<T>::~QueueLinked() {
    clear();
}

template <typename T>
QueueLinked<T>::QueueLinked(const QueueLinked& other) : front_ptr(nullptr), rear_ptr(nullptr), size(0) {
    copyFrom(other);
}

template <typename T>
QueueLinked<T>& QueueLinked<T>::operator=(const QueueLinked& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
void QueueLinked<T>::enqueue(const T& item) {
    Node* newNode = new Node(item);
    
    if (isEmpty()) {
        front_ptr = rear_ptr = newNode;
    } else {
        rear_ptr->next = newNode;
        rear_ptr = newNode;
    }
    size++;
}

template <typename T>
T QueueLinked<T>::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    
    Node* temp = front_ptr;
    T item = temp->data;
    
    front_ptr = front_ptr->next;
    if (front_ptr == nullptr) {
        rear_ptr = nullptr;  // Queue is now empty
    }
    
    delete temp;
    size--;
    return item;
}

template <typename T>
const T& QueueLinked<T>::front() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    return front_ptr->data;
}

template <typename T>
const T& QueueLinked<T>::rear() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    return rear_ptr->data;
}

template <typename T>
bool QueueLinked<T>::isEmpty() const {
    return front_ptr == nullptr;
}

template <typename T>
int QueueLinked<T>::getSize() const {
    return size;
}

template <typename T>
void QueueLinked<T>::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}

template <typename T>
void QueueLinked<T>::display() const {
    if (isEmpty()) {
        std::cout << "Queue is empty" << std::endl;
        return;
    }
    
    std::cout << "Queue: ";
    Node* current = front_ptr;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) std::cout << " <- ";
        current = current->next;
    }
    std::cout << " (front: " << front_ptr->data << ", rear: " << rear_ptr->data << ")" << std::endl;
}

template <typename T>
void QueueLinked<T>::copyFrom(const QueueLinked& other) {
    if (other.isEmpty()) {
        return;
    }
    
    Node* current = other.front_ptr;
    while (current != nullptr) {
        enqueue(current->data);
        current = current->next;
    }
}

#endif // QUEUE_LINKED_H
