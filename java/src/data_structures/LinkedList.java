package data_structures;

import java.util.*;

/**
 * Singly Linked List Implementation in Java
 * 
 * Time Complexity:
 * - Insert at head: O(1)
 * - Insert at tail: O(1) with tail reference
 * - Insert at index: O(n)
 * - Delete at head: O(1)
 * - Delete at tail: O(n) without doubly linked
 * - Delete at index: O(n)
 * - Search: O(n)
 * - Access by index: O(n)
 * 
 * Space Complexity: O(n) where n is the number of elements
 */
public class LinkedList<T> implements Iterable<T> {
    
    /**
     * Node class for the linked list
     */
    private static class Node<T> {
        T data;
        Node<T> next;
        
        Node(T data) {
            this.data = data;
            this.next = null;
        }
    }
    
    private Node<T> head;    // Reference to first node
    private Node<T> tail;    // Reference to last node
    private int size;        // Current number of elements
    
    /**
     * Constructor - Initialize empty linked list
     */
    public LinkedList() {
        this.head = null;
        this.tail = null;
        this.size = 0;
    }
    
    /**
     * Constructor with initial elements
     * @param elements Initial elements to add
     */
    @SafeVarargs
    public LinkedList(T... elements) {
        this();
        for (T element : elements) {
            pushBack(element);
        }
    }
    
    /**
     * Constructor from collection
     * @param collection Collection to initialize from
     */
    public LinkedList(Collection<T> collection) {
        this();
        for (T element : collection) {
            pushBack(element);
        }
    }
    
    /**
     * Add element to the front of the list
     * @param data Element to add
     */
    public void pushFront(T data) {
        Node<T> newNode = new Node<>(data);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode.next = head;
            head = newNode;
        }
        size++;
    }
    
    /**
     * Add element to the back of the list
     * @param data Element to add
     */
    public void pushBack(T data) {
        Node<T> newNode = new Node<>(data);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail.next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    /**
     * Insert element at specific index
     * @param index Position to insert at
     * @param data Element to insert
     * @throws IndexOutOfBoundsException if index is invalid
     */
    public void insert(int index, T data) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
        }
        
        if (index == 0) {
            pushFront(data);
            return;
        }
        
        if (index == size) {
            pushBack(data);
            return;
        }
        
        Node<T> newNode = new Node<>(data);
        Node<T> current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current.next;
        }
        
        newNode.next = current.next;
        current.next = newNode;
        size++;
    }
    
    /**
     * Remove element from the front of the list
     * @return The removed element
     * @throws NoSuchElementException if list is empty
     */
    public T popFront() {
        if (isEmpty()) {
            throw new NoSuchElementException("List is empty");
        }
        
        T data = head.data;
        head = head.next;
        
        if (head == null) {
            tail = null;
        }
        
        size--;
        return data;
    }
    
    /**
     * Remove element from the back of the list
     * @return The removed element
     * @throws NoSuchElementException if list is empty
     */
    public T popBack() {
        if (isEmpty()) {
            throw new NoSuchElementException("List is empty");
        }
        
        if (size == 1) {
            return popFront();
        }
        
        Node<T> current = head;
        while (current.next != tail) {
            current = current.next;
        }
        
        T data = tail.data;
        tail = current;
        tail.next = null;
        size--;
        return data;
    }
    
    /**
     * Remove element at specific index
     * @param index Position to remove from
     * @return The removed element
     * @throws IndexOutOfBoundsException if index is invalid
     */
    public T removeAt(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
        }
        
        if (index == 0) {
            return popFront();
        }
        
        if (index == size - 1) {
            return popBack();
        }
        
        Node<T> current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current.next;
        }
        
        Node<T> nodeToRemove = current.next;
        T data = nodeToRemove.data;
        current.next = nodeToRemove.next;
        size--;
        return data;
    }
    
    /**
     * Remove first occurrence of element
     * @param data Element to remove
     * @return true if element was found and removed, false otherwise
     */
    public boolean remove(T data) {
        if (isEmpty()) {
            return false;
        }
        
        if (Objects.equals(head.data, data)) {
            popFront();
            return true;
        }
        
        Node<T> current = head;
        while (current.next != null && !Objects.equals(current.next.data, data)) {
            current = current.next;
        }
        
        if (current.next == null) {
            return false; // Element not found
        }
        
        Node<T> nodeToRemove = current.next;
        current.next = nodeToRemove.next;
        
        if (nodeToRemove == tail) {
            tail = current;
        }
        
        size--;
        return true;
    }
    
    /**
     * Get element at specific index
     * @param index Position to get element from
     * @return Element at index
     * @throws IndexOutOfBoundsException if index is invalid
     */
    public T get(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
        }
        
        Node<T> current = head;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        return current.data;
    }
    
    /**
     * Set element at specific index
     * @param index Position to set element at
     * @param data New element value
     * @return Previous element at index
     * @throws IndexOutOfBoundsException if index is invalid
     */
    public T set(int index, T data) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
        }
        
        Node<T> current = head;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        
        T oldData = current.data;
        current.data = data;
        return oldData;
    }
    
    /**
     * Get first element
     * @return First element
     * @throws NoSuchElementException if list is empty
     */
    public T getFirst() {
        if (isEmpty()) {
            throw new NoSuchElementException("List is empty");
        }
        return head.data;
    }
    
    /**
     * Get last element
     * @return Last element
     * @throws NoSuchElementException if list is empty
     */
    public T getLast() {
        if (isEmpty()) {
            throw new NoSuchElementException("List is empty");
        }
        return tail.data;
    }
    
    /**
     * Find index of first occurrence of element
     * @param data Element to search for
     * @return Index of element, or -1 if not found
     */
    public int indexOf(T data) {
        Node<T> current = head;
        int index = 0;
        
        while (current != null) {
            if (Objects.equals(current.data, data)) {
                return index;
            }
            current = current.next;
            index++;
        }
        
        return -1; // Not found
    }
    
    /**
     * Check if element exists in the list
     * @param data Element to search for
     * @return true if found, false otherwise
     */
    public boolean contains(T data) {
        return indexOf(data) != -1;
    }
    
    /**
     * Check if list is empty
     * @return true if empty, false otherwise
     */
    public boolean isEmpty() {
        return size == 0;
    }
    
    /**
     * Get current size of list
     * @return Number of elements in list
     */
    public int size() {
        return size;
    }
    
    /**
     * Clear all elements from list
     */
    public void clear() {
        head = null;
        tail = null;
        size = 0;
    }
    
    /**
     * Reverse the linked list
     */
    public void reverse() {
        if (size <= 1) return;
        
        Node<T> prev = null;
        Node<T> current = head;
        tail = head; // Old head becomes new tail
        
        while (current != null) {
            Node<T> next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        
        head = prev; // prev is now the new head
    }
    
    /**
     * Convert list to array
     * @return Array containing all elements
     */
    @SuppressWarnings("unchecked")
    public T[] toArray() {
        T[] array = (T[]) new Object[size];
        Node<T> current = head;
        int index = 0;
        
        while (current != null) {
            array[index++] = current.data;
            current = current.next;
        }
        
        return array;
    }
    
    /**
     * Convert list to ArrayList
     * @return ArrayList containing all elements
     */
    public List<T> toList() {
        List<T> list = new ArrayList<>(size);
        Node<T> current = head;
        
        while (current != null) {
            list.add(current.data);
            current = current.next;
        }
        
        return list;
    }
    
    /**
     * Create a copy of this linked list
     * @return New LinkedList with same elements
     */
    public LinkedList<T> copy() {
        LinkedList<T> newList = new LinkedList<>();
        Node<T> current = head;
        
        while (current != null) {
            newList.pushBack(current.data);
            current = current.next;
        }
        
        return newList;
    }
    
    /**
     * Iterator implementation
     */
    @Override
    public Iterator<T> iterator() {
        return new LinkedListIterator();
    }
    
    private class LinkedListIterator implements Iterator<T> {
        private Node<T> current = head;
        
        @Override
        public boolean hasNext() {
            return current != null;
        }
        
        @Override
        public T next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            T data = current.data;
            current = current.next;
            return data;
        }
    }
    
    /**
     * String representation of the list
     */
    @Override
    public String toString() {
        if (isEmpty()) {
            return "[]";
        }
        
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        
        Node<T> current = head;
        while (current != null) {
            sb.append(current.data);
            if (current.next != null) {
                sb.append(", ");
            }
            current = current.next;
        }
        
        sb.append("]");
        return sb.toString();
    }
    
    /**
     * Equals method for comparing lists
     */
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        
        LinkedList<?> other = (LinkedList<?>) obj;
        if (size != other.size) return false;
        
        Node<T> current1 = head;
        Node<?> current2 = other.head;
        
        while (current1 != null) {
            if (!Objects.equals(current1.data, current2.data)) {
                return false;
            }
            current1 = current1.next;
            current2 = current2.next;
        }
        
        return true;
    }
    
    /**
     * Hash code implementation
     */
    @Override
    public int hashCode() {
        int hash = 1;
        Node<T> current = head;
        
        while (current != null) {
            hash = 31 * hash + Objects.hashCode(current.data);
            current = current.next;
        }
        
        return hash;
    }
}
