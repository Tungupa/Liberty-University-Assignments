#ifndef LINK_H
#define LINK_H

template <typename E>
class Link {
public:
    E element;      // The element stored in the node
    int frequency;  // Frequency of accesses (how many times the node is accessed)
    Link* next;     // Pointer to the next node

    // Constructor to initialize the node, frequency starts at 0
    Link(const E& elem) : element(elem), frequency(0), next(nullptr) {}
};

#endif  // LINK_H
