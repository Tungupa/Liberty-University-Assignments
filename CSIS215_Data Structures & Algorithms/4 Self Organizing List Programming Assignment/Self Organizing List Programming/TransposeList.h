#ifndef TRANSPOSE_LIST_H
#define TRANSPOSE_LIST_H

#include "SelfOrderedListADT.h"
#include <iostream>

template <typename E>
class TransposeList : public SelfOrderedListADT<E> {
private:
    struct Node {
        E value;
        int frequency; // Tracks how often this node has been accessed
        Node* next;

        Node(const E& val, Node* nxt = nullptr)
            : value(val), frequency(1), next(nxt) {} // Initialize frequency to 1
    };

    Node* head;   // Pointer to the head of the list
    int compares; // Total number of comparisons
    int listSize; // Number of elements in the list

public:
    TransposeList() : head(nullptr), compares(0), listSize(0) {}

    ~TransposeList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool find(const E& it) override {
        Node* prev = nullptr;
        Node* curr = head;

        while (curr) {
            compares++; // Increment global comparison count

            if (curr->value == it) { // Found the node
                curr->frequency++; // Increment frequency of the node

                // Check if the node is already at the head
                if (curr == head) {
                    return true; // No need to swap; already at the front
                }

                // Error Check: Ensure prev is valid before swapping
                if (!prev) {
                    std::cerr << "Error: Previous node is null during swapping!" << std::endl;
                    return false; // Terminate to avoid invalid access
                }

                // Swap logic: Move current node one step closer to the front
                prev->next = curr->next; // Detach curr from the list
                curr->next = prev;      // Point curr to prev
                if (prev == head) {
                    head = curr; // Update head if prev was the first node
                } else {
                    // Find the node before `prev` to update its `next` pointer
                    Node* temp = head;
                    while (temp && temp->next != prev) {
                        temp = temp->next; // Traverse to find the node before prev
                    }
                    if (temp) {
                        temp->next = curr; // Update the node pointing to prev
                    } else {
                        std::cerr << "Error: Node before previous not found!" << std::endl;
                    }
                }

                // Final check: Ensure no circular references were created
                if (curr->next == curr) {
                    std::cerr << "Error: Circular reference detected!" << std::endl;
                    return false;
                }

                return true;
            }

            // Move prev and curr pointers forward
            prev = curr;
            curr = curr->next;
        }

        // If not found, add the new item to the list
        add(it);
        return false;
    }

    void add(const E& it) override {
        Node* newNode = new Node(it); // Frequency is initialized to 1 in the Node constructor
        if (!head) {
            head = newNode; // If the list is empty, set the new node as the head
        } else {
            Node* temp = head;
            while (temp->next) { // Traverse to the end of the list
                temp = temp->next;
            }
            temp->next = newNode; // Add the new node to the end
        }
        listSize++; // Increment the size of the list
    }

    int getCompares() const override {
        return compares;
    }

    int size() const override {
        return listSize;
    }

    void printlist() override {
        Node* temp = head;
        while (temp) {
            std::cout << temp->value << "-" << temp->frequency << " "; // Display value and frequency
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void printlist(int n) override {
        Node* temp = head;
        int count = 0;
        while (temp && count < n) {
            std::cout << temp->value << "-" << temp->frequency << " "; // Display value and frequency
            temp = temp->next;
            count++;
        }
        std::cout << std::endl;
    }
};

#endif
