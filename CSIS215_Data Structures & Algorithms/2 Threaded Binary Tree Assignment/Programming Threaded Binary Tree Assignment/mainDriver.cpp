//Citations:
//In reseaching how to do this I used the following sources :
//1. Data Structures and Algorithm Analysis Edition 3.2 (C++ Version)Clifford A.Shaffer
//2. Youtube : Did a bunch or tutorials on both data structure and C++
//3. Stackoverflow : Looked up examples of a binary tree and a threaded binary tree.
//4. ChatGPT : Give examples of how to to use boolean flags.
//5. Google : did a lot of searches in Binary trees/threaded binary tree and implemtation in C++.
#include <iostream>
#include <string>
#include "BST.h"

int main() 
{
    BST<int, std::string> tree;

    tree.insert(77, "seventy-seven");
    tree.insert(70, "seventy");
    tree.insert(75, "seventy-five");
    tree.insert(66, "sixty-six");
    tree.insert(79, "seventy-nine");
    tree.insert(68, "sixty-eight");
    tree.insert(67, "sixty-seven");
    tree.insert(69, "sixty-nine");
    tree.insert(90, "ninety");
    tree.insert(85, "eighty-five");
    tree.insert(83, "eighty-three");
    tree.insert(87, "eighty-seven");
    tree.insert(65, "sixty-five");

    // Print the tree structure
    std::cout << "<Pi-Tumbasa Puli> -- CSIS 215 Programming Assignment 2 -- Double Binary Threaded Search Tree"
        << std::endl << std::endl;
    std::cout << "My BST tree size is " << tree.size() << "\n";
    tree.printhelp();
    std::cout << std::endl;

    // Print the inorder traversal of the tree
    std::cout << "Inorder printing of my tree:\n";
    tree.printInorder();
    std::cout << std::endl;

    // Print the reverse order traversal of the tree
    std::cout << "Reverse order printing of my tree:\n";
    tree.printReverse();
    std::cout << std::endl;

    return 0;
}
