#pragma once
#ifndef BST_H
#define BST_H

#include "BSTNode.h"
#include <iostream>
#include <iomanip>
using namespace std;

template <typename Key, typename E>
class BST 
{
    private:
        BSTNode<Key, E>* root;    // Root of the BST
        int nodecount;            // Number of nodes in the BST

        // Private helper functions
        BSTNode<Key, E>* inserthelp(BSTNode<Key, E>* node, const Key& k, const E& e);
        void printhelp(BSTNode<Key, E>* node, int depth) const;
        void printInorderHelper() const;
        void printReverseHelper() const;

    public:
        BST() : root(nullptr), nodecount(0) {}

        void insert(const Key& k, const E& e)
        {
            root = inserthelp(root, k, e);
            nodecount++;
        }

        void printInorder() const { printInorderHelper(); }
        void printReverse() const { printReverseHelper(); }
        void printhelp() const
        {
            cout << "Tree structure (Inorder traversal):" << endl;
            printhelp(root, 0);
        }

        int size() const { return nodecount; }
};

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* node, const Key& k, const E& e) 
{
    BSTNode<Key, E>* parent = nullptr;
    BSTNode<Key, E>* current = node;

    // Loops until it finds to correct position for the new node or reaches a thread.
    while (current) 
    {
        parent = current;
        if (k < current->key()) 
        {
            if (current->isLeftThread()) break;
            current = current->left();
        }
        else 
        {
            if (current->isRightThread()) break;
            current = current->right();
        }
    }

    BSTNode<Key, E>* newNode = new BSTNode<Key, E>(k, e);
    if (parent == nullptr) 
    {
        // Tree was empty, new node is root
        root = newNode;
    }
    else if (k < parent->key()) 
    {
        newNode->setLeft(parent->left(), true);
        newNode->setRight(parent, true);
        parent->setLeft(newNode, false);
    }
    else 
    {
        newNode->setRight(parent->right(), true);
        newNode->setLeft(parent, true);
        parent->setRight(newNode, false);
    }

    return node ? node : newNode;
}

// Print the BST in inorder without recursion
template <typename Key, typename E>
void BST<Key, E>::printInorderHelper() const 
{
    BSTNode<Key, E>* current = root;
    while (current && !current->isLeftThread()) 
    {
        current = current->left();
    }

    while (current) 
    {
        cout << current->element() << endl;

        if (current->isRightThread()) {
            current = current->right();
        }
        else 
        {
            current = current->right();
            while (current && !current->isLeftThread()) 
            {
                current = current->left();
            }
        }
    }
}

// Print the BST in reverse order without recursion
template <typename Key, typename E>
void BST<Key, E>::printReverseHelper() const 
{
    BSTNode<Key, E>* current = root;
    while (current && !current->isRightThread()) 
    {
        current = current->right();
    }

    while (current) 
    {
        cout << current->element() << endl;

        if (current->isLeftThread()) 
        {
            current = current->left();
        }
        else 
        {
            current = current->left();
            while (current && !current->isRightThread()) 
            {
                current = current->right();
            }
        }
    }
}

// Helper function to print the tree structure in inorder traversal
template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* node, int depth) const 
{
    if (node == nullptr) return;

    // Traverse left subtree
    if (!node->isLeftThread()) 
    {
        printhelp(node->left(), depth + 1);
    }

    // Print current node
    cout << setw(depth * 4) << "" << node->key() << endl;

    // Traverse right subtree
    if (!node->isRightThread()) 
    {
        printhelp(node->right(), depth + 1);
    }
}

#endif
