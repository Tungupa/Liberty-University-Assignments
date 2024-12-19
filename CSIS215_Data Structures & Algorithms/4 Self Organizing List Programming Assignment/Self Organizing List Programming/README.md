# Approach Documentation
As always, the first step to accomplishing this task was to understand the problem. From the assignment documentation, I needed to understand how the count heuristic, the move-to-front heuristic and transpose heuristic self-organizing list works.
Let us look at the count heuristic first. What I need to accomplish with this list is to keep a list ordered by frequency by storing a count of accesses to each record. According to my reading the count heuristic is like the least frequently used buffer replacement strategy.  Whenever a record is accessed, it is counted. If its count is greater than the count of the record proceeding it, it is moved to the front. So basically, my count methods/class should count the frequency and swap the record based on the count.
The following shows the possible pseudo code for the count heuristic class.
Initialize an empty list (ordered by frequency)
Initialize an empty dictionary to store access counts (e.g., frequency_dict)
Function find(record):
    If record is found in frequency_dict:
        Increment the access count of the record in frequency_dict
        Reorder the list:
            - Move the record toward the front of the list if its access count becomes greater than a record(s) in front of it
    Else:
        Add the record to frequency_dict with an initial access count of 1
        Add the record to the list in its appropriate position (can be at the end for new records)
    Return the result (True if found, False if not found)
Function add(record):
    If record is not in frequency_dict:
        Add record to frequency_dict with an initial access count of 1
        Add the record to the list in its appropriate position
    Else:
        Call find(record) to update access count and reorder
 
Function reorder_list():
    Sort the list of records based on their frequency in descending order
    Update the list based on the new order
    This keeps the most frequently accessed records near the front of the list
 
Function print_list():
    For each record in the list:
        Print the record and its frequency
The basic explanation is that the function checks if the record exists, if so, its count is incremented. After that it is reordered. If the record does not exist, it is added to the list and incremented.
Now the next self-organizing list that I need to understand is the move-to-front heuristic. According to my reading, this algorithm, after finding a record, just moves it to the front, pushing all the other records back one position. In addition, this heuristic is easy to implement if the records are stored in a linked list. Now I needed a refresh of what a link-list is. A link-list is a data structure where data is stored in a sequence. The interesting thing is that each element of the list does not only contain information on that element, it has information, more accurately references to the next element. This allows for dynamic insertion and deletion of elements at any position without needing to change the entire structure of the list. Now how does this assist me. When a record is accessed, it has information on what record was in front of it. It uses that to know what record to swap out.
The following is pseudocode for a Move-To-Front Heuristic list:
Initialize an empty list (linked list)
Initialize an empty dictionary (frequency_dict) to store access counts (optional, depending on whether you track frequency)
Function find(record):
    If record is found in the list:
        - Move the record to the front of the list
        - Increment the access count of the record (optional)
        Return True (record found)
    Else:
        - Add the record to the front of the list
        - Initialize the access count to 1 (optional)
        Return False (record not found)
Function add(record):
    - Add the record to the front of the list (it will be considered a new record with initial access count of 1)
    - Optionally, update frequency_dict to track the number of accesses if needed
Function print_list():
    For each record in the list:
        - Print the record and its access count (if tracking frequency)
A basic explanation for this is that when the record is found, it moves it to the front of the list.  Like the previous self-organizing list, it has an add method and a print method as well.
Now let us look at the final self-organizing list, the transpose heuristic. The transpose heuristic works by swapping an accessed record with the one right before it in the list. This is great for both linked lists and arrays because it helps frequently accessed records move toward the front, while those that are less accessed naturally drift toward the back. It adapts well to changes in access patterns. 
Here is the possible pseudocode for the transpose heuristic.
Function TransposeHeuristic(List, accessedRecord):
    Search the list for the accessedRecord:
        If the record is found:
            Find the position of the accessedRecord in the list (currentPosition).
            If currentPosition > 0 (record is not at the front):
                Swap the accessedRecord with the record at currentPosition - 1.
            Update the list after the swap.
        If the record is not found:
            Add the record to the end of the list.
            Set the frequency to 1.
    Return the updated list.
 
Repeat this process for each access to the list.
Now the final class that is worth mentioning is the llist.h class. This is the implementation of the linked list. The key components of a node in this class will be the element, frequency and next pointer. The element is the actual data. The frequency is the count of how many times the node’s data has been accessed. The next pointer points to the next node.
The class overall is responsible for inserting nodes, searching nodes, removing nodes, traversing the list and checking the size of the list.
Basically, the llist.h file provides the basic linked list data structure and operations that are used by the different heuristics.
The other classes and functions, for example, the the main.cpp will be written around this goal. This will be the approach I will use to accomplish this assignment.

