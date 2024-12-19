#pragma once
// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This is the file to include for access to the complete binary node
// template implementation

#include "book.h"
#include "BinNode.h"

#ifndef BSTNODE_H
#define BSTNODE_H

// Simple binary search tree node implementation with threading support
template <typename Key, typename E>
class BSTNode 
{
    private:
        Key k;                   // The node's key
        E it;                    // The node's value
        BSTNode* lc;             // Pointer to left child or thread
        BSTNode* rc;             // Pointer to right child or thread
        bool leftThread;         // True if lc is a thread
        bool rightThread;        // True if rc is a thread

    public:
        // Constructors
        BSTNode() 
        {
            lc = nullptr;
            rc = nullptr;
            leftThread = false;
            rightThread = false;
        }

        BSTNode(Key K, E e, BSTNode* l = nullptr, BSTNode* r = nullptr) 
        {
            k = K;
            it = e;
            lc = l;
            rc = r;
            leftThread = false;
            rightThread = false;
        }

        // Destructor
        ~BSTNode() {}             

        // Functions to set and return the value and key
        E& element() { return it; }
        void setElement(const E& e) { it = e; }

        Key& key() { return k; }
        void setKey(const Key& K) { k = K; }

        // Functions to set and return the children
        BSTNode* left() const { return lc; }
        void setLeft(BSTNode* b, bool isThread) 
        {
            lc = b;
            leftThread = isThread;
        }

        BSTNode* right() const { return rc; }
        void setRight(BSTNode* b, bool isThread) 
        {
            rc = b;
            rightThread = isThread;
        }

        // Thread indicators
        bool isLeftThread() const { return leftThread; }
        bool isRightThread() const { return rightThread; }
};

#endif
