#ifndef COUNTLIST_H
#define COUNTLIST_H

#include "SelfOrderedListADT.h"
#include "Link.h"

template <typename E>
class CountList : public SelfOrderedListADT<E> {
private:
    Link<E>* head;  // The head of the list
    int compares;    // Tracks the number of compares

public:
    CountList() : head(nullptr), compares(0) {}

    virtual ~CountList() {
        // Clean up memory when the list is destroyed
        while (head != nullptr) {
            Link<E>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Access the head of the list (Moved here from SelfOrderedListADT)
    Link<E>* getHead() const {
        return head;
    }

    // Find method to access and reorder the list based on frequency
    virtual bool find(const E& it) override {
        Link<E>* current = head;
        Link<E>* prev = nullptr;

        // Traverse the list to find the element
        while (current != nullptr) {
            compares++;
            if (current->element == it) {
                // Found the element, increment its frequency
                current->frequency++;
                reorder(); // Reorder after incrementing frequency
                return true;
            }
            prev = current;
            current = current->next;
        }

        // If element is not found, add it to the list with frequency set to 1
        Link<E>* newNode = new Link<E>(it);  // Frequency is initialized to 0 by default
        newNode->frequency = 1;  // Set frequency to 1 explicitly when adding a new node
        newNode->next = head;
        head = newNode;
        return false;
    }

    virtual void add(const E& it) override {
        // Add a new node with element 'it' and frequency set to 1
        Link<E>* newNode = new Link<E>(it);  // Frequency initialized to 0
        newNode->frequency = 1;  // Set frequency to 1 explicitly
        newNode->next = head;
        head = newNode;
    }

    virtual int getCompares() const override {
        return compares;
    }

    virtual int size() const override {
        int size = 0;
        Link<E>* temp = head;
        while (temp != nullptr) {
            size++;
            temp = temp->next;
        }
        return size;
    }

    virtual void printlist() override {
        // Print all nodes in the list along with their frequency
        Link<E>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->element << "-" << temp->frequency << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    virtual void printlist(int n) override {
        // Print the first 'n' nodes in the list with their frequency
        Link<E>* temp = head;
        int count = 0;
        while (temp != nullptr && count < n) {
            std::cout << temp->element << "-" << temp->frequency << " ";
            temp = temp->next;
            count++;
        }
        std::cout << std::endl;
    }

private:
    // Reorders the list based on frequencies (higher frequency moves towards the front)
    void reorder() {
        if (head == nullptr || head->next == nullptr) {
            return;  // No need to reorder if the list is empty or has one element
        }

        Link<E>* current = head;
        bool swapped;

        do {
            swapped = false;
            current = head;

            while (current != nullptr && current->next != nullptr) {
                // Compare frequencies of adjacent nodes
                if (current->frequency < current->next->frequency) {
                    // Swap if the current node's frequency is less than the next node
                    E tempElement = current->element;
                    int tempFrequency = current->frequency;

                    current->element = current->next->element;
                    current->frequency = current->next->frequency;

                    current->next->element = tempElement;
                    current->next->frequency = tempFrequency;

                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped); // Keep swapping until no more swaps are needed
    }
};

#endif  // COUNTLIST_H
