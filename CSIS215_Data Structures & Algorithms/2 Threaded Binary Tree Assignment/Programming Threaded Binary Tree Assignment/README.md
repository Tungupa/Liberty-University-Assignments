# Approach Documentation
My plan to accomplish this assignment is first to understand it. The first thing I must do is to know what a Double Binary Threaded Search Tree is. I will first need to understand how threads work and how they differ from child pointers.
In a normal binary tree, each node has three fields, the left pointer, the data and the right pointer. All the nodes that will be connected to the left child pointer will be less than the root and all the nodes connected to the right child will be greater than the root.
Traversal in a binary search tree is based on this structure. For example, to insert a value
In a binary search tree, that value is compared to the root, if it is less than the root, it is inserted to the left of the root, and if it is greater, to the right of the root. Once a node is inserted, it also will have three fields, but if it does not have children, the left and right points will point to null.
This is the background information I need to understand how a Double Binary Threaded Search Tree works. In a DBTST the pointers that point to null can be used as threads.
The left thread points to the in-order predecessor and the right thread points to the in-order successor.
The goal is to convert a regular BST to a DBTST.  In the DBTST there are a total of 5 fields in a node. I will need a left thread, left pointer, data, right pointer and right thread. The left and right thread are Boolean values. This values chech whether the left or right points are threads. 
To understand this better, let's say I need to insert a value that is less than the node into the DBTST, first the program will traverse the tree to the correct position by comparing the new value with the values in the tree. Once that position is reached, the node is inserted, and the left and right pointers are updated. Let's say that the left pointer has a child, meaning there was a value less than the new value, its left thread will equal false because it has a child and does not need to be threaded.  Now on the other hand let us assume the right pointer is null. Since it does not have a child, the right thread will be set to true, so the point will point to its successor (a greater value).

BSTNODE.H
Now let us first look at the BSTNode.h and how it got modified to have two thread methods.
The thread methods are “isLeftThread()” and “isRightThread”. They are added to the private class of the BSTNode class.

Again, they are flags that if true, means that there is a null that needs to be converted to a thread.
Something important to note is that, when creating a node, both left and right threads will be false, and both pointers will be null because we do not know if the node has children yet. Hence the constructor will look like: 

The getter and setter functions for the left and right children of a node in tje allow manipulation of both pointers and threads. The left() function returns the left child, which may be a pointer to another node or a thread, while setLeft(b, isThread) sets the left child to b and specifies whether it is a thread using the isThread flag. Similarly, right() returns the right child (either a pointer or a thread), and setRight(b, isThread) sets the right child and marks it as a thread if applicable.

BST.H
A summary of the BST class functionality is as follows: 
    1. inserting nodes (insert), 
    2. printing the tree in in-order (printInorder) 
    3. and reverse in-order (printReverse) traversals, 
    4. and displaying the tree's structure with node depth (printhelp). 
The inserthelp function inserts nodes while maintaining the threaded structure, adjusting left and right pointers based on key comparisons. 
The tree supports non-recursive in-order and reverse traversals using threads to efficiently navigate through missing children. 
The first method insert(), inserts a new node with the specified key and value into the tree. It calls the inserthelp() method to manage the insertion.

 (Implementation in the maiDriver.cpp)
Now to the most important method the inserthelp(). This method inserts a new node by first starting at the root and traverses down the tree until it finds the correct spot for the new node. The methods setLeft and setRight are used to set the thread based on the key values. It then updates the pointers accordingly. 
If the new key k is smaller than the current node’s key, it checks if the left pointer is a thread (using isLeftThread()). If it is a thread, it means there are no left children, and we can insert the new node here. Otherwise, it moves to the left child (current = current->left()).
Similarly, if k is larger than or equal to the current node’s key, it checks if the right pointer is a thread (using isRightThread()). If it is a thread, it means there are no right children, and we can insert the new node here. Otherwise, it moves to the right child (current = current->right()).

 
Basically, the method starts at the root and compares the new node's key with the current node’s key. It traverses down the tree, moving left or right based on the comparison, until it reaches a position where a thread or null child pointer is found.
Once the correct position is identified, the new node is inserted, adjusting pointers and threads.
The next function (printinorderHelper) basically prints the tree in the in-order format (left, root then right). It accomplishes this without the use of recursion but my following the threading structure.
It starts by setting the current point to the root of the tree and aims at finding the leftmost node. This will be the first node that will be printed. It loops through the nodes, comparing it to the current node, checking to see if the node has a left child. When it finds a node that has null as a left child, that would be the leftmost node.
It then prints the left most node and checks that current node to see if the right child is a thread. If it is a thread, it will be pointing to the next highest number. This traversal will continue until it reaches the right most node in the tree. Since the right child of the right most node will be null, the traversal will end.
In summary, The method inserts a new node into the binary search tree (BST) while maintaining its threading structure. It starts by traversing the tree, comparing the new node’s key (k) with the current node’s key, and moving left or right accordingly.
    1. Traversal: It moves left or right based on the key comparison, and checks if a thread is encountered using isLeftThread() or isRightThread(). The traversal stops when an appropriate position is found, either when reaching a thread or a nullPtr.
    2. Node Creation: Once the correct position is found, a new node is created.
    3. Insertion: The new node is inserted by updating the parent’s left or right pointer, depending on whether the key is smaller or larger than the parent’s key. The appropriate threads are set to connect the new node with the tree.
    4. Return: The method returns the updated tree with the new node properly inserted.

This same process will be repeated for the reverse order traversal but this time the goal will be to find the rightmost child. It will just check to see if the right child is a null, if it is not, the current value is updated and that is checked. Finally, it will reach null on the right side and that node’s value will be printed. Then it will check the left thread to see if it points to another lesser value node. It will print that next and move up the tree checking for less values until it reaches the leftmost node which its left child is null, and the traversal ends.



