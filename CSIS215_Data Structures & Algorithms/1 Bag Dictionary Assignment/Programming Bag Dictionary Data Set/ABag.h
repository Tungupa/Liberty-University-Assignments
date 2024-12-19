#ifndef ABAG_H
#define ABAG_H

#include "kvpair.h"
#include <iostream>
#include <string>

//######################## CLASS START ####################################
template <typename E>
class ABag {
public:
    ABag(int cap);           // Constructor with capacity
    ABag();                  // Default constructor
    ~ABag();                 // Destructor

    void emptyBag();         // Clear all items
    bool addItem(const E& item);     // Add an item
    bool remove(const E& item);      // Remove an item
    bool find(const E& item) const;  // Find an item
    bool removeTop(E& item);         // Remove the top item
    int size() const;                // Get the size of the bag

    // Functions that will be tested in myBagDemo()
    bool inspectTop(E& item) const;     // Inspect the top item
    bool operator+=(const E& addend);   // Add item using += operator
    int bagCapacity() const;            // Get the capacity of the bag

    // Function to demonstrate bag functionality
    void myBagDemo(); 

private:
    E* data;           // Array to hold the items
    int capacity;      // Maximum capacity of the bag
    int currentSize;   // Current size of the bag
};
//####################### CLASS END #########################################

// Implementation of methods

//###################### MEMORY ALLOCATION/DEALLOCATION START #####################
template <typename E>
ABag<E>::ABag(int cap) : capacity(cap), currentSize(0)
{
    data = new E[capacity]; // Dynamic array allocation
}

template <typename E>
ABag<E>::ABag() : capacity(10), currentSize(0) {
    data = new E[capacity]; // Default capacity set to 10
}

template <typename E>
ABag<E>::~ABag() {
    delete[] data; // Release the allocated memory
}
//###################### MEMORY ALLOCATION/DEALLOCATION END ######################

//###################### EMPTYBAG() START ##########################################
/*
Clears the bag by resetting currentSize to 0, effectively "removing" all items
without deallocating memory.
*/
template <typename E>
void ABag<E>::emptyBag() 
{
    currentSize = 0; 
}
//###################### EMPTYBAG() END ############################################

//###################### ADDITEM() START ###########################################
/*
Adds an item to the bag if it is not full, incrementing currentSize.
Returns false if the bag is already at capacity.
*/
template <typename E>
bool ABag<E>::addItem(const E& item) 
{
    if (currentSize < capacity) 
    {
        data[currentSize++] = item;
        return true; 
    }
    return false; 
}
//###################### ADDITEM() END #############################################

//###################### REMOVE() START ############################################
/*
Finds and removes the specified item by replacing it with the last item in the array, 
reducing currentSize. This keeps the array compact without shifting elements.
*/

template <typename E>
bool ABag<E>::remove(const E& item) 
{
    for (int i = 0; i < currentSize; ++i) 
    {
        if (data[i] == item)
        {
            data[i] = data[--currentSize];
            return true; 
        }
    }
    return false; 
}
//###################### REMOVE() END ##############################################

//###################### FIND() START ##############################################
/*
Searches for the specified item in the array. If found, returns true; 
otherwise, returns false.
*/
template <typename E>
bool ABag<E>::find(const E& item) const 
{
    for (int i = 0; i < currentSize; ++i) 
    {
        if (data[i] == item) 
        {
            return true; 
        }
    }
    return false; 
}
//###################### FIND() END ################################################

//###################### REMOVETOP() START ##########################################
/*
Removes the most recently added item (top item) from the bag, storing it in item. 
Returns false if the bag is empty.
*/
template <typename E>
bool ABag<E>::removeTop(E& item) 
{
    if (currentSize > 0) 
    {
        item = data[--currentSize]; // Return the top item and decrement size
        return true; 
    }
    return false;
}
//###################### REMOVETOP() END ###########################################

//###################### SIZE() START ##############################################
/*
Returns the current number of items in the bag.
*/
template <typename E>
int ABag<E>::size() const 
{
    return currentSize; 
}
//###################### SIZE() END ################################################

//###################### INSPECTTOP() START ########################################
/*
Retrieves the top item without removing it. 
Returns true if the bag is not empty, otherwise false.
*/
template <typename E>
bool ABag<E>::inspectTop(E& item) const
{
    if (currentSize > 0) {
        item = data[currentSize - 1]; // Copy the top item without removing it
        return true; 
    }
    return false; 
}
//###################### INSPECTTOP() END ##########################################

//###################### OPERATOR+=() START ########################################
/*
Allows adding an item to the bag using +=, by calling addItem.
*/
template <typename E>
bool ABag<E>::operator+=(const E& addend) 
{
    return addItem(addend); // Use addItem to add an item with += operator
}
//###################### OPERATOR+=() END ##########################################

//###################### BAGCAPACITY() START #######################################
/*
Returns the maximum capacity of the bag.
*/
template <typename E>
int ABag<E>::bagCapacity() const 
{
    return capacity; 
}
//###################### BAGCAPACITY() END #########################################

//###################### MYBAGDEMO() START #########################################
/*
Adds items using +=.
Outputs the bag's capacity and current size.
Demonstrates inspectTop and removeTop.
Clears the bag with emptyBag and displays the updated size.
*/
template <typename E>
void ABag<E>::myBagDemo() 
{
    std::cout << "Demonstrating ABag functionality:\n";

    // Use operator+= to add items to the bag
    *this += KVpair<int, std::string>(1, "Item One");
    *this += KVpair<int, std::string>(2, "Item Two");
    *this += KVpair<int, std::string>(3, "Item Three");

    // Output the capacity of the bag
    std::cout << "Bag capacity: " << this->bagCapacity() << std::endl;

    // Output current size of the bag
    std::cout << "Current size of the bag: " << this->size() << std::endl;

    // Demonstrate inspectTop without removing the item
    KVpair<int, std::string> topItem;
    if (this->inspectTop(topItem)) 
    {
        std::cout << "Inspected top item (without removing): Key = " 
                  << topItem.key() << ", Value = " << topItem.value() << std::endl;
    } else 
    {
        std::cout << "Failed to inspect top item; the bag might be empty." << std::endl;
    }

    // Demonstrate removeTop to actually remove the top item
    if (this->removeTop(topItem)) 
    {
        std::cout << "Removed top item: Key = " << topItem.key() 
                  << ", Value = " << topItem.value() << std::endl;
    } else 
    {
        std::cout << "Failed to remove top item; the bag might be empty." << std::endl;
    }

    // Output size after removal
    std::cout << "Size of the bag after removing top item: " << this->size() << std::endl;

    // Now empty the bag
    this->emptyBag();
    std::cout << "Bag emptied. Current size: " << this->size() << std::endl;
}
//###################### MYBAGDEMO() END ###########################################

#endif // ABAG_H
