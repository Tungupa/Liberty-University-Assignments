# Approach Documentation
The first step to undertaking this assignment is to understand how the LRU algorithm works.
From doing research the following are the main functions that allow the LRU algorithm to work within this assignment scope.
Doubly Link List
For the LRU algorithm to work, we need to be able to organize the blocks where the newest block will be placed at the front of the list. As the space allocated to the blocks is filled up, the block at the end of the list is removed. The doubly link list manages this activity and keeps the blocks in this order.
Hash Map
Now using the doubly link list, we can insert and remove blocks from the list, but how do we know what is in the list? This would be helpful to see if a block is being accessed frequently. We can use a hash map   to check the blocks quickly. This is better than traversing the list. Using a primary key, which will be the block ID, we can look up that block to see if it is on the list.
Replacement/Add
Now we have got the basic structure down with the two concepts above. We can investigate more detail on how a block will be removed or added. Let's say I have 5 blocks that are empty, and I put the number 1 in block 1, 2 is block 2, etc. When I reach 5, the 6 data input into the buffer will not have an empty block. In this function, I will need to check the size of the pool and if it is less than the amount of data I am putting in, I will need to remove the “1” from block 1 to make space for 6. This is because 1 would be the lease recently used block. 


Moving Blocks to Front
Now if a block is being referenced constantly, that block must be the most recently used block. I will need to write a function that will check to see if a block is being requested, that block needs to be moved to the front. In my example, block 5 has 5 in it, and if 4 keeps being referenced the number 4 is moved into the front block which is 5.

This way the block that is being accessed the most will be kept in front of the list and will less likely be removed.

Buffer Pool Size
Another crucial piece would be the buffer pool size. This would just contain the size of the blocks. If the size is exceeded, the Add/Remove function would remove the blocks at the end of the list.
Loader
Another function that I would need would be to load data from the test file into the blocks. This function would check to see if the data is not already in the pool, and if it is not there, it would load the new data into the pool.
BufferBlock.h
To create my BufferBlock class first would be the constructors and destructors.

 The important thing to note is that the constructor uses the memset function to initialize the block. It copies the block size into the block. To test it out, the following function, show if it was successful.

 

Next would be the setID and getID. This would be for the block ID that would be used in the hash mapping to find a block in the pool. Next would be getData. This would be the data that is in the text file that will be read into the block. 

Basically, this just  creates and ID (setID) and points to the block's location in the pool if needed(getID). To test it out the following test function was created:
So how it works is the block ID is set to 123. If this works correctly, I will be able to use the GetID function to retrieve the ID. The test function checks this.

We would then need a setBlock and getBlock function to manipulate the blocks themselves. The setBlock would be to create the block and the getblock would be to access the block.

The important thing to note about the above functions is how the setBlock works. The memcpy function copies the data from blk(the test data), it then puts it into block. It also references the specified size it needs to copy using Block Size. Again, the following test functions show how it works.

Using the  strcmp function, we can compare the block that we inputted some test data. If the geBlock retrieves the exact data, it shows that both the setBlock and getBlock are working.

The next we would need  a function check the block size. This will help when trying to check to see if all the blocks are full.

The test for this is pretty straightforward. We create a new block and get its size. It should be the default size.

The final function that my BufferBlock class would need is the getData method. Basically, I would need a function to get the data from the test file and input it into a block.

The important thing to note here is that when if the data size that inputted is greater than the block size, it is adjusted to fit the block size. This allows the function to retrieve a portion of data from a large block of data.

To test, we create an array called buffer with a size of bytes. We then use the getData function to test if we can retrieve just part of the data we assigned to the array. In this case, the word “Hello”. After checking we see that the function has correctly retrieved part of the data from the whole array.

Now that my BufferBlock class has been created and tested, we can move on to creating the LRUBufferPool class.
LRUBufferPool.h
Now this is where I used the linked list to create the pool. This data type (list) allows for efficient insertion and removal of items at any position.

To keep track of the blocks, this is where I use the hash mapping.

By using the unordered_map template, I can store the data in key-value pairs. This will allow me to access each block by looking at their keys instead of traversing the list to find it.
Now the third important item, to be specific, function, that is needed will be something that can load a block of data from the file into the pool. This will be the loadBlock function.
The function starts off by allocating memory for the data. It allocates a temporary buffer to hold the block of data being read.  It then moves the file pointer to the start of the block to be read.

The line above is one of the most important lines because is calculates the byte offset in the file where the block begins. It then ensures that the offset is calculated from the beginning of the file. The data is then read into the buffer.
Next the bufferBlock is created and initialized. The ID of the block is set and the data from the temporary variable is copied into the buffer block using setBlock.

And yes, the temporary data is deleted to free it up for the next read.
Next is the implementation of the buffer pool. Basically, when the pool is full, it removes the least recently used block. It also clears the block ID and clears the memory. The implementation is shown below.

The next part is pretty straightforward. Whether or not the pool is full, data needs to be added. The following functions move the new block to the front and add it to the hash mapping.


This concludes the private data types and functions. Now let's look at the public functions of the class.
We all know that the class needs constructors and destructors. The constructor basically reads in the file and the destructor removes it after it goes out of scope.

Now the next function is the most important function of this system. This function is called the getBytes function. This function does 4 things:
    1. It identifies which block the requested data resides and determining a starting point within the block.

    2. If the block is not already in memory it calls the loadBlock function to create a block.

    3. It moves the block to the front of the pool by adjusting its position.

    4. It allows data revival using the memory space.
    5. 
Basically, this ensures that file data is retrieved efficiently, blocks are managed properly, and the most recently used blocks are prioritized in the cache.
In conclusion, the implementation of the LRU Cache leverages a doubly linked list and a hash map to efficiently manage file blocks in memory. The doubly linked list maintains the order of blocks, with the most recently used (MRU) at the front and the least recently used (LRU) at the back, allowing efficient addition and removal. The hash map provides fast lookups to determine if a block is already in the buffer pool, using block IDs as keys. When the buffer pool exceeds its size, the LRU block is removed to make space for new data. Frequently accessed blocks are moved to the front to prioritize them, ensuring efficient retrieval and optimal memory usage while interacting with the file.


