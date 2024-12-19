/*
//Citations:
In reseaching how to do this I used the following sources :
1. Data Structures and Algorithm Analysis Edition 3.2 (C++ Version)Clifford A.Shaffer
2. Youtube : Did a bunch or tutorials on both data structure and C++
3. Stackoverflow : Looked up examples of a binary tree and a threaded binary tree.
4. ChatGPT : Give examples of how to to impelement a LRU buffer pool
5. Google : did a lot of searches in Binary trees/threaded binary tree and implemtation in C++.
        
*/
#include "BufferPoolADT.h"
#include "BufferBlock.h"
#include "constants.h"
#include <list>
#include <unordered_map>
#include <fstream>
#include <iostream>

class LRUBufferPool : public BufferPoolADT 
{
    private:
        std::string filename;
        int poolSize;
        int blockSize;
        std::list<BufferBlock*> bufferPool;           // LRU buffer pool implemented as a doubly linked list
        std::unordered_map<int, BufferBlock*> blockMap; // Maps block ID to its respective buffer block
        std::ifstream file;

        /*
        The loadBlock function is a helper method that loads a specific block of data from the file 
        into the buffer pool, ensuring efficient caching while adhering to the LRU (Least Recently Used) 
        strategy. It begins by allocating memory for the block data and reading the specified block 
        (blockID) from the file at the correct offset. A new BufferBlock object is created and initialized 
        with the block ID and the retrieved data. If the buffer pool is already full, the least recently 
        used (LRU) block is identified, removed from both the buffer pool and the hash map, and its memory is 
        deallocated. The newly loaded block is then added to the front of the buffer pool 
        (marking it as the most recently used) and inserted into the hash map for quick access. This function 
        ensures that the buffer pool maintains its size limit while keeping frequently accessed blocks 
        readily available.
        */
        void loadBlock(int blockID) 
        {
            char* data = new char[blockSize];
            file.seekg(blockID * blockSize, std::ios::beg);
            file.read(data, blockSize);  

            BufferBlock* block = new BufferBlock();
            block->setID(blockID);
            block->setBlock(data);  
            delete[] data;

            // If buffer pool is full, remove the least recently used block
            if (bufferPool.size() == poolSize) 
            {
                BufferBlock* lru = bufferPool.back();
                blockMap.erase(lru->getID());  // Remove the LRU block from the map
                bufferPool.pop_back();         // Remove the LRU block from the list
                delete lru;                    
            }

            bufferPool.push_front(block);       // Move the newly accessed block to the front (most recently used)
            blockMap[blockID] = block;          // Add the block to the map
        }

    public:
        // Constructor:
        LRUBufferPool(std::string filename, int poolSize = 5, int blockSize = 4096)
            : filename(filename), poolSize(poolSize), blockSize(blockSize) 
        {
            file.open(filename, std::ios::binary);
            if (!file.is_open()) 
            {
                throw std::runtime_error("Error opening file.");
            }
        }

        // Destructor:
        ~LRUBufferPool() 
        {
            for (auto block : bufferPool) 
            {
                delete block; 
            }
            file.close();
        }
        
        /*
        The getBytes function is designed to efficiently retrieve a specified number of bytes 
        (sz) of data from a given position (pos) in a file while managing the buffer pool using
        the LRU (Least Recently Used) caching strategy. It first calculates the block ID and 
        the offset within the block based on the position. If the block containing the requested 
        data is not already in the buffer pool, the function loads it from the file using the 
        loadBlock method. The block is then retrieved from the hash map and moved to the front
        of the doubly linked list to mark it as the most recently used (MRU). Finally, the 
        function retrieves the data from the block using the getData method, ensuring that the 
        data is efficiently loaded into memory and the buffer pool maintains its LRU order. 
        This mechanism ensures fast access to frequently used data while optimizing memory usage.
        */
        void getBytes(char* space, int sz, int pos) override 
        {
            int blockID = pos / blockSize;         // Calculate the block ID from the position
            int offset = pos % blockSize;          // Calculate the offset within the block

            // If the block is not already in the pool, load it
            if (blockMap.find(blockID) == blockMap.end()) 
            {
                loadBlock(blockID);  
            }

            // Retrieve the block from the map
            BufferBlock* block = blockMap[blockID];

            // Move the accessed block to the front (most recently used)
            bufferPool.remove(block);       // Remove the block from its current position
            bufferPool.push_front(block);   // Insert the block at the front

            // Get the requested data from the block
            block->getData(offset, sz, space);

        }

        // Method to print the order of buffer blocks, from most recently used to least recently used
        void printBufferBlockOrder() override 
        {
            std::cout << "My buffer block order from most recently used to LRU is:\n";  
            for (auto block : bufferPool) 
            {
                std::cout << "\t" << block->getID() << ",";  
            }
            std::cout << "\n";
        }

        // Method to get the ID of the least recently used (LRU) block
        int getLRUBlockID() override 
        {
            if (bufferPool.empty()) return -1;  // If no blocks are in the pool, return -1
            return bufferPool.back()->getID(); // Return the ID of the LRU block (last in the list)
        }
};
