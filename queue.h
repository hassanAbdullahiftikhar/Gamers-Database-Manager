#pragma once
#include<iostream>
using namespace std;
template<typename T>
struct Node {
    Node* next;
    T* a; // Pointer to T

    Node() : next(nullptr), a(nullptr) {}  // Default constructor

    Node(T* i) : a(i), next(nullptr) {}   // Constructor that accepts a pointer
};
template<typename T>
class Queue {
    Node<T>* front;
    Node<T>* tail;
public:
    Queue() : front(nullptr), tail(nullptr) {}

    void enqueue(T* i) {
        Node<T>* newNode = new Node<T>(i); // Create new node with pointer to T
        if (front == nullptr) {
            front = tail = newNode;  // First node
        }
        else {
            tail->next = newNode;  // Add to the end of the queue
            tail = newNode;  // Update tail to the new node
        }
    }

    T* top() {
        return front ? front->a : nullptr;  // Return pointer to T stored in the front node
    }

    void dequeue() {
        if (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;  // Deallocate the old front node
            if (front == nullptr) {
                tail = nullptr;  // If the queue is empty, set tail to nullptr
            }
        }
    }

    bool is_empty() {
        return front == nullptr;
    }
};