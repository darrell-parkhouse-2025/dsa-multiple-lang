#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>

/**
 * Singly Linked List Implementation in C++
 * 
 * Time Complexity:
 * - Insert at head: O(1)
 * - Insert at tail: O(1) with tail pointer
 * - Insert at index: O(n)
 * - Delete at head: O(1)
 * - Delete at tail: O(n) without doubly linked
 * - Delete at index: O(n)
 * - Search: O(n)
 * - Access by index: O(n)
 * 
 * Space Complexity: O(n) where n is the number of elements
 */
template <typename T>
class LinkedList {
private:
    /**
     * Node structure for the linked list
     */
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;     // Pointer to first node
    Node* tail;     // Pointer to last node
    size_t size;    // Current number of elements

public:
    /**
     * Constructor - Initialize empty linked list
     */
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    /**
     * Constructor with initializer list
     */
    LinkedList(std::initializer_list<T> init) : head(nullptr), tail(nullptr), size(0) {
        for (const auto& item : init) {
            pushBack(item);
        }
    }
    
    /**
     * Copy constructor
     */
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        copyFrom(other);
    }
    
    /**
     * Assignment operator
     */
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }
    
    /**
     * Destructor - Clean up all nodes
     */
    ~LinkedList() {
        clear();
    }
    
    /**
     * Add element to the front of the list
     * @param value Element to add
     */
    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    
    /**
     * Add element to the back of the list
     * @param value Element to add
     */
    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    /**
     * Insert element at specific index
     * @param index Position to insert at
     * @param value Element to insert
     * @throws std::out_of_range if index is invalid
     */
    void insert(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            pushFront(value);
            return;
        }
        
        if (index == size) {
            pushBack(value);
            return;
        }
        
        Node* newNode = new Node(value);
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
    
    /**
     * Remove element from the front of the list
     * @return The removed element
     * @throws std::underflow_error if list is empty
     */
    T popFront() {
        if (isEmpty()) {
            throw std::underflow_error("List is empty");
        }
        
        Node* temp = head;
        T value = temp->data;
        
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        
        delete temp;
        size--;
        return value;
    }
    
    /**
     * Remove element from the back of the list
     * @return The removed element
     * @throws std::underflow_error if list is empty
     */
    T popBack() {
        if (isEmpty()) {
            throw std::underflow_error("List is empty");
        }
        
        if (size == 1) {
            return popFront();
        }
        
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        
        T value = tail->data;
        delete tail;
        tail = current;
        tail->next = nullptr;
        size--;
        return value;
    }
    
    /**
     * Remove element at specific index
     * @param index Position to remove from
     * @return The removed element
     * @throws std::out_of_range if index is invalid
     */
    T removeAt(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        if (index == 0) {
            return popFront();
        }
        
        if (index == size - 1) {
            return popBack();
        }
        
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        Node* nodeToDelete = current->next;
        T value = nodeToDelete->data;
        current->next = nodeToDelete->next;
        delete nodeToDelete;
        size--;
        return value;
    }
    
    /**
     * Remove first occurrence of value
     * @param value Value to remove
     * @return true if element was found and removed, false otherwise
     */
    bool remove(const T& value) {
        if (isEmpty()) {
            return false;
        }
        
        if (head->data == value) {
            popFront();
            return true;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        
        if (current->next == nullptr) {
            return false; // Value not found
        }
        
        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        
        if (nodeToDelete == tail) {
            tail = current;
        }
        
        delete nodeToDelete;
        size--;
        return true;
    }
    
    /**
     * Get element at specific index
     * @param index Position to get element from
     * @return Reference to element at index
     * @throws std::out_of_range if index is invalid
     */
    T& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    /**
     * Get element at specific index (const version)
     */
    const T& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    /**
     * Get first element
     * @return Reference to first element
     * @throws std::underflow_error if list is empty
     */
    T& front() {
        if (isEmpty()) {
            throw std::underflow_error("List is empty");
        }
        return head->data;
    }
    
    /**
     * Get first element (const version)
     */
    const T& front() const {
        if (isEmpty()) {
            throw std::underflow_error("List is empty");
        }
        return head->data;
    }
    
    /**
     * Get last element
     * @return Reference to last element
     * @throws std::underflow_error if list is empty
     */
    T& back() {
        if (isEmpty()) {
            throw std::underflow_error("List is empty");
        }
        return tail->data;
    }
    
    /**
     * Get last element (const version)
     */
    const T& back() const {
        if (isEmpty()) {
            throw std::underflow_error("List is empty");
        }
        return tail->data;
    }
    
    /**
     * Find index of first occurrence of value
     * @param value Value to search for
     * @return Index of value, or -1 if not found
     */
    int find(const T& value) const {
        Node* current = head;
        int index = 0;
        
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        
        return -1; // Not found
    }
    
    /**
     * Check if value exists in the list
     * @param value Value to search for
     * @return true if found, false otherwise
     */
    bool contains(const T& value) const {
        return find(value) != -1;
    }
    
    /**
     * Check if list is empty
     * @return true if empty, false otherwise
     */
    bool isEmpty() const {
        return size == 0;
    }
    
    /**
     * Get current size of list
     * @return Number of elements in list
     */
    size_t getSize() const {
        return size;
    }
    
    /**
     * Clear all elements from list
     */
    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }
    
    /**
     * Reverse the linked list
     */
    void reverse() {
        if (size <= 1) return;
        
        Node* prev = nullptr;
        Node* current = head;
        tail = head; // Old head becomes new tail
        
        while (current != nullptr) {
            Node* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev; // prev is now the new head
    }
    
    /**
     * Display list contents (for debugging)
     */
    void display() const {
        if (isEmpty()) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "List: ";
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << " (size: " << size << ")" << std::endl;
    }
    
    /**
     * Operator[] for array-like access
     */
    T& operator[](size_t index) {
        return at(index);
    }
    
    /**
     * Operator[] for array-like access (const version)
     */
    const T& operator[](size_t index) const {
        return at(index);
    }

private:
    /**
     * Helper function to copy from another list
     */
    void copyFrom(const LinkedList& other) {
        Node* current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }
};

#endif // LINKED_LIST_H
