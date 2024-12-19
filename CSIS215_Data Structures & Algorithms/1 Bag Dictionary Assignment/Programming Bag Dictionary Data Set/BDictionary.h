// BDictionary.h
#ifndef BDICTIONARY_H
#define BDICTIONARY_H

#include "ABag.h"
#include "dictionaryADT.h"
#include "kvpair.h"
#include <string>

/*This template class, BDictionary, provides a dictionary (key-value pair storage) 
using a generic ABag container. It derives from the Dictionary abstract class 
to ensure it implements a consistent set of dictionary operations. BDictionary 
provides methods for inserting, removing, finding, and clearing key-value pairs, 
as well as getting the dictionary's size. The Key and E template parameters allow 
flexibility in defining the types used for keys and values.
*/

template <typename Key, typename E>
class BDictionary : public Dictionary<Key, E> 
{
    public:
        BDictionary(int cap);             // Constructor with capacity
        ~BDictionary();                   // Destructor
        void clear() override;            // Clear all items
        bool insert(const Key& k, const E& e) override; // Insert a key-value pair
        bool remove(const Key& k, E& rtnVal) override;  // Remove a specific key
        bool removeAny(E& returnValue) override;        // Remove any item
        bool find(const Key& k, E& returnValue) const override; // Find a key
        int size() override;              // Return the size of the dictionary

    private:
        ABag<KVpair<Key, E>>* dictionary; // Pointer to an ABag object holding KV pairs
};

// Implementation of template methods

// Constructor: Initializes a new ABag with a specified capacity to store key-value pairs.
template <typename Key, typename E>
BDictionary<Key, E>::BDictionary(int cap) 
{
    dictionary = new ABag<KVpair<Key, E>>(cap);
}

// Destructor: Releases memory allocated for the ABag dictionary.
template <typename Key, typename E>
BDictionary<Key, E>::~BDictionary() 
{
    delete dictionary;
}

// Clear Method: Empties the dictionary by invoking emptyBag on the underlying ABag object.
template <typename Key, typename E>
void BDictionary<Key, E>::clear() 
{
    dictionary->emptyBag();
}

// Insert Method: Adds a new key-value pair to the dictionary. Returns true on success 
// or false if the dictionary is at full capacity.
template <typename Key, typename E>
bool BDictionary<Key, E>::insert(const Key& k, const E& e) 
{
    KVpair<Key, E> newPair(k, e);
    return dictionary->addItem(newPair);
}

/* Remove Method: Finds and removes a key-value pair with the specified key. 
If the key is found, the corresponding value is returned in rtnVal and true 
is returned. If the key is not found, returns false.
*/
template <typename Key, typename E>
bool BDictionary<Key, E>::remove(const Key& k, E& rtnVal) 
{
    KVpair<Key, E> temp(k, E());
    for (int i = 0; i < dictionary->size(); ++i) 
    {
        if (dictionary->find(temp)) 
        {
            rtnVal = temp.value(); // Set return value
            dictionary->remove(temp); // Remove the key-value pair
            return true; // Successfully removed
        }
    }
    return false; // Key not found
}

// RemoveAny Method: Removes and returns any key-value pair from the dictionary, 
// storing the value in returnValue. If the dictionary is empty, returns false.
template <typename Key, typename E>
bool BDictionary<Key, E>::removeAny(E& returnValue) 
{
    KVpair<Key, E> pair;
    if (dictionary->removeTop(pair)) 
    { 
        returnValue = pair.value(); // Get the value of removed pair
        return true; // Successfully removed
    }
    return false; // Dictionary is empty
}

/* Find Method: Searches for a key in the dictionary. If the key is found, 
the associated value is stored in returnValue and true is returned. If the key 
does not exist in the dictionary, returns false.
*/
template <typename Key, typename E>
bool BDictionary<Key, E>::find(const Key& k, E& returnValue) const 
{
    KVpair<Key, E> temp(k, E());
    if (dictionary->find(temp)) 
    { 
        returnValue = temp.value(); // Get the value associated with the key
        return true; // Key found
    }
    return false; // Key not found
}

// Size Method: Returns the number of key-value pairs currently stored in the dictionary.
template <typename Key, typename E>
int BDictionary<Key, E>::size()  
{
    return dictionary->size(); // Return the size of the bag
}

template class BDictionary<int, std::string>;
template class BDictionary<std::string, int>;

#endif // BDICTIONARY_H
